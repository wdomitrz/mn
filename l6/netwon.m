function img=netwon
WIDTH = 1024;
HEIGHT = 1024;
range = [-2, 2, -2, 2];
nIteration = 50;
tolerance = 0.0005;
func = @(z)(z .^ 5 - 1);
funcprim = @(z)(5 .* z .^ 4);
trans = @(zn, k, ix, iy, n)(if (abs(zn(ix, iy) - z0(ix, iy)) < tolerance) k(ix, iy) = min(k(ix, iy), n)  )
x = linspace(range(1), range(2), WIDTH);
y = linspace(range(3), range(4), HEIGHT);
img = nIteration * ones(WIDTH, HEIGHT);
z = x' + i * y;

k = 1
while n < nIteration
    zn = z - func(z) ./ funcprim(z);
    k = @(z

for n = 1 : nPoint
    k = 1;
    z0 = X(n) + i*Y(n);
    zn = 0+ i*0;
    while k < nIteration
        zn = z0 - func(z0) / funcprim(z0);
        if abs(zn - z0) < tolerance
            break;
        end
        z0 = zn;
        k = k+1;
    end
    if mod(n, 100) == 0
        disp(n);
        disp(k)
    end
    img(n) = k;
end

imagesc(img);
end
