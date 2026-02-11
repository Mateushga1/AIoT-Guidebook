# callbacks_torch.py
import math
from typing import Dict, List, Optional

import matplotlib
import matplotlib.pyplot as plt
from IPython.display import display, clear_output

# Matplotlib settings to avoid font / LaTeX issues (same idea as your TF code)
matplotlib.rcParams.update({
    'font.family': 'sans-serif',
    'font.sans-serif': ['DejaVu Sans', 'Liberation Sans'],
    'text.usetex': False
})

# ----------------------------
# A minimal callback base API
# ----------------------------
class Callback:
    def on_train_begin(self, logs: Optional[Dict] = None): ...
    def on_epoch_begin(self, epoch: int, logs: Optional[Dict] = None): ...
    def on_epoch_end(self, epoch: int, logs: Optional[Dict] = None): ...
    def on_train_end(self, logs: Optional[Dict] = None): ...

class CallbackList:
    """Utility to broadcast events to a list of callbacks."""
    def __init__(self, callbacks: Optional[List[Callback]] = None):
        self.callbacks = callbacks or []

    def on_train_begin(self, logs: Optional[Dict] = None):
        for cb in self.callbacks:
            cb.on_train_begin(logs)

    def on_epoch_begin(self, epoch: int, logs: Optional[Dict] = None):
        for cb in self.callbacks:
            cb.on_epoch_begin(epoch, logs)

    def on_epoch_end(self, epoch: int, logs: Optional[Dict] = None):
        for cb in self.callbacks:
            cb.on_epoch_end(epoch, logs)

    def on_train_end(self, logs: Optional[Dict] = None):
        for cb in self.callbacks:
            cb.on_train_end(logs)

# -------------------------------------------
# AccuracyPlotCallback (PyTorch-compatible)
# -------------------------------------------
class AccuracyPlotCallback(Callback):
    """
    Real-time plot of accuracy and validation accuracy at each epoch end.

    Expected keys in `logs` on each epoch_end:
      - 'accuracy' or 'acc'
      - 'val_accuracy' or 'val_acc'
    """
    def __init__(self, title: str = 'Training Progress: Accuracy vs. Epochs'):
        self.epochs: List[int] = []
        self.accuracies: List[float] = []
        self.val_accuracies: List[float] = []
        self.title = title

    def on_train_begin(self, logs=None):
        # reset state if reused
        self.epochs.clear()
        self.accuracies.clear()
        self.val_accuracies.clear()

    def on_epoch_end(self, epoch: int, logs: Optional[Dict] = None):
        logs = logs or {}
        # accept either accuracy/acc and val_accuracy/val_acc to be flexible
        acc = logs.get('accuracy', logs.get('acc'))
        val_acc = logs.get('val_accuracy', logs.get('val_acc'))

        # Safeguards: if metrics are missing, skip plotting for that epoch
        if acc is None or (val_acc is None):
            # You can also choose to append NaNs and still plot
            return

        self.epochs.append(epoch + 1)
        self.accuracies.append(float(acc))
        self.val_accuracies.append(float(val_acc))

        clear_output(wait=True)
        plt.figure(figsize=(8, 5))
        plt.plot(self.epochs, self.accuracies, color='red', linewidth=3,
                 label="Training Accuracy", marker="o")
        plt.plot(self.epochs, self.val_accuracies, color='blue', linewidth=3,
                 label="Validation Accuracy", marker="o")
        plt.tick_params(axis='y', labelsize=16)
        plt.tick_params(axis='x', labelsize=16)
        plt.xticks(fontsize=16)
        plt.yticks(fontsize=16)
        plt.xlabel('Epochs', fontsize=20)
        plt.ylabel('Accuracy', fontsize=20)
        plt.title(self.title, fontsize=18)
        plt.legend(fontsize=16)
        plt.grid(True)
        display(plt.gcf())
        plt.tight_layout()
        plt.close()

# ---------------------------------------------------------
# count_neurons_and_synapses (PyTorch version)
# ---------------------------------------------------------
def _unwrap_compiled_model(model):
    """
    If model was wrapped by torch.compile, some PyTorch versions expose the
    original Module via attributes like _orig_mod. We try to recover it;
    otherwise we just return the input as-is.
    """
    # Known attribute for compiled models in recent PyTorch releases
    if hasattr(model, "_orig_mod"):
        return model._orig_mod
    return model

def count_neurons_and_synapses(model):
    """
    Prints a summary analogous to your TF helper.
    For now we focus on nn.Linear (equivalent to Keras Dense).
    """
    import torch.nn as nn

    model = _unwrap_compiled_model(model)

    print("\n--- Model Summary (Neurons and Synapses) ---")
    total_neurons = 0
    total_synapses = 0

    for name, module in model.named_modules():
        # Skip the top-level model entry (which is the whole model itself)
        if name == '':
            continue

        layer_name = name
        layer_type = type(module).__name__

        # nn.Linear ~ Dense
        if isinstance(module, nn.Linear):
            out_features = module.out_features
            in_features = module.in_features
            has_bias = module.bias is not None

            # Parameters = in_features*out_features (+ out_features if bias)
            num_weights = in_features * out_features
            num_bias = out_features if has_bias else 0
            synapses = num_weights + num_bias

            # Count parameters using PyTorch API (trainable + non-trainable == all params for nn.Linear)
            params = sum(p.numel() for p in module.parameters())

            total_neurons += out_features
            total_synapses += synapses

            print(
                f"Layer: {layer_name} ({layer_type}), "
                f"Parameters: {params}, "
                f"Neurons: {out_features}, "
                f"Weights: {num_weights}, "
                f"Bias: {num_bias}, "
                f"Calculated Synapses (Weights + Bias): {synapses}"
            )

        # You can add convolutional layers here similarly if/when needed:
        # elif isinstance(module, nn.Conv2d):
        #     pass

    print(f"\nTotal Neurons (approx, mainly from Linear): {total_neurons}")
    print(f"Total Synapses (Total Trainable Parameters): {total_synapses}")