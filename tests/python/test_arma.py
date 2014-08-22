import excentury as xc
import arma

print arma.inverse_det(xc.array([[1.0, 2], [3, 4]]))
print arma.qr(xc.array([[1.0, 2], [3, 4]]))
print arma.solve(xc.array([[1.0, 2], [3, 4]]), xc.array([[1.0], [2.0]]))
