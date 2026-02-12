import numpy as np
from intel_npu_acceleration_library.backend import MatMul
import time

inC, outC, batch = 8192, 8192, 512
X1 = np.random.uniform(-1, 1, (batch, inC)).astype(np.float16)
X2 = np.random.uniform(-1, 1, (outC, inC)).astype(np.float16)

mm = MatMul(inC, outC, batch, profile=True)

start = time.time()
for i in range(20):  # repeat 20 times
    result = mm.run(X1, X2)
end = time.time()

print("MatMul complete. Result shape:", result.shape)
print("Total time:", end-start)
