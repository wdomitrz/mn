% [u, u0] = rrc_jacobi_method(@(x, y) 0, @(x, y) 1, 20, 1/20, 10);
% figure(1)
% mesh(u)
% grid
% figure(2)
% mesh(u0)
% grid

[u, u0] = rrc_jacobi_method(@(x, y) rand(1,1) + 5, @(x, y) 1, 20, 1/20, 10);
figure(1)
mesh(u)
grid
figure(2)
mesh(u0)
grid
