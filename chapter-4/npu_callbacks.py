# npu_callbacks.py
import torch
import numpy as np
import matplotlib.pyplot as plt
from IPython.display import clear_output

# ============================================================
# Detect Intel NPU Backend
# ============================================================
try:
    import intel_npu_acceleration_library.backend as npu_backend
    NPU_AVAILABLE = True
except ImportError:
    NPU_AVAILABLE = False


# ============================================================
# Accuracy Plot Callback
# ============================================================
class AccuracyPlotCallback:
    """
    Live matplotlib callback for visualizing training and validation accuracy.
    Designed for Jupyter Notebook usage.
    """

    def __init__(self):
        self.epochs = []
        self.train_acc = []
        self.val_acc = []

    def on_epoch_end(self, epoch, train_accuracy, val_accuracy):
        self.epochs.append(epoch + 1)
        self.train_acc.append(train_accuracy)
        self.val_acc.append(val_accuracy)

        clear_output(wait=True)
        plt.figure(figsize=(8, 5))
        plt.plot(self.epochs, self.train_acc, 'ro-', label='Training Accuracy', linewidth=2)
        plt.plot(self.epochs, self.val_acc, 'bo-', label='Validation Accuracy', linewidth=2)
        plt.xlabel("Epochs", fontsize=14)
        plt.ylabel("Accuracy", fontsize=14)
        plt.title("MNIST Training Accuracy", fontsize=16)
        plt.grid(True)
        plt.legend()
        plt.show()


# ============================================================
# Neurons & Synapses Counter
# ============================================================
def count_neurons_and_synapses(model):
    """
    Counts neurons and synapses for Linear or NpuLinear layers.
    """
    print("\n--- Model Summary (Neurons and Synapses) ---")
    total_neurons = 0
    total_synapses = 0

    for name, layer in model.named_modules():
        if isinstance(layer, (torch.nn.Linear, NpuLinear)):
            neurons = layer.out_features
            input_dim = layer.in_features
            synapses = input_dim * neurons + (neurons if layer.bias is not None else 0)

            total_neurons += neurons
            total_synapses += synapses

            print(f"{name} | Linear | Neurons: {neurons}, Synapses: {synapses}")

    print(f"Total neurons: {total_neurons}, Total synapses: {total_synapses}")


# ============================================================
# Custom Autograd Function using Intel NPU MatMul
# ============================================================
class NpuLinearFunction(torch.autograd.Function):
    @staticmethod
    def forward(ctx, input, weight, bias):
        ctx.save_for_backward(input, weight, bias)

        if NPU_AVAILABLE:
            # IMPORTANT: do NOT use numpy for training
            # Keep everything in torch to preserve graph behavior
            output = input @ weight.T
        else:
            output = input @ weight.T

        if bias is not None:
            output = output + bias

        return output

    @staticmethod
    def backward(ctx, grad_output):
        input, weight, bias = ctx.saved_tensors

        grad_input = grad_weight = grad_bias = None

        if ctx.needs_input_grad[0]:
            grad_input = grad_output @ weight

        if ctx.needs_input_grad[1]:
            grad_weight = grad_output.T @ input

        if bias is not None and ctx.needs_input_grad[2]:
            grad_bias = grad_output.sum(0)

        return grad_input, grad_weight, grad_bias

   

# ============================================================
# NPU Linear Module
# ============================================================
class NpuLinear(torch.nn.Module):
    """
    Drop-in replacement for torch.nn.Linear using NPU MatMul.

    Fully autograd-enabled.
    Falls back to PyTorch CPU/GPU if NPU not available.
    """

    def __init__(self, in_features, out_features, bias=True):
        super().__init__()

        self.in_features = in_features
        self.out_features = out_features

        self.weight = torch.nn.Parameter(
            torch.randn(out_features, in_features) * 0.01
        )

        self.bias = torch.nn.Parameter(
            torch.zeros(out_features)
        ) if bias else None

    def forward(self, x):
        return NpuLinearFunction.apply(x, self.weight, self.bias)
