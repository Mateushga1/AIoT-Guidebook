import tensorflow as tf
import matplotlib.pyplot as plt
import matplotlib
from IPython.display import display, clear_output

# Matplotlib settings to avoid font and LaTeX errors
matplotlib.rcParams.update({
    'font.family': 'sans-serif',
    'font.sans-serif': ['DejaVu Sans', 'Liberation Sans'],
    'text.usetex': False
})

# Define the callback class to plot accuracy in real-time
class AccuracyPlotCallback(tf.keras.callbacks.Callback):
    def __init__(self):
        self.epochs = []
        self.accuracies = []
        self.val_accuracies = []

    def on_epoch_end(self, epoch, logs=None):
        self.epochs.append(epoch + 1)
        self.accuracies.append(logs['accuracy'])
        self.val_accuracies.append(logs['val_accuracy'])
        clear_output(wait=True)
        plt.plot(self.epochs, self.accuracies, color='red', linewidth=3, label="Training Accuracy", marker="o")
        plt.plot(self.epochs, self.val_accuracies, color='blue', linewidth=3, label="Validation Accuracy", marker="o")
        plt.tick_params(axis='y', labelsize=16)
        plt.tick_params(axis='x', labelsize=16)
        plt.xticks(fontsize=16)
        plt.yticks(fontsize=16)
        plt.xlabel('Epochs', fontsize=20)
        plt.ylabel('Accuracy', fontsize=20)
        plt.title('Training Progress: Accuracy vs. Epochs', fontsize=18)
        plt.legend(fontsize=16)
        plt.grid(True)
        display(plt.gcf())
        plt.tight_layout()
        plt.close()

def count_neurons_and_synapses(model):
    
    print("\n--- Model Summary (Neurons and Synapses) ---")
    total_neurons = 0
    total_synapses = 0

    for layer in model.layers:
        layer_name = layer.name
        layer_type = type(layer).__name__
        params = layer.count_params() # Total parameters (weights + biases)
        
        neurons = "N/A"
        synapses = "N/A"
        
        if isinstance(layer, tf.keras.layers.Dense):
            neurons = layer.units
            # For a Dense layer, parameters = (input * neurons) + neurons (bias)
            if layer.kernel is not None and layer.kernel.shape:
                input_dim = layer.kernel.shape[0]
                num_weights = input_dim * neurons
                num_bias = neurons if layer.use_bias else 0
                synapses = num_weights + num_bias # Synapses are weights + bias
                
                total_neurons += neurons
                total_synapses += synapses
                
                print(f"Layer: {layer_name} ({layer_type}), Parameters: {params}, Neurons: {neurons}, Weights: {num_weights}, Bias: {num_bias}, Calculated Synapses (Weights + Bias): {synapses}")
            else:
                # If not possible to calculate, just print basic information
                print(f"Layer: {layer_name} ({layer_type}), Parameters: {params}, Neurons: {neurons}, Synapses: could not fully calculate")

        elif isinstance(layer, tf.keras.layers.Conv2D):
            # Logic for Conv2D
            pass # We just ignore this for this example

        # Add other layer types here if needed
        
    print(f"\nTotal Neurons (approx, mainly from Dense/RNN): {total_neurons}")
    print(f"Total Synapses (Total Trainable Parameters): {total_synapses}")