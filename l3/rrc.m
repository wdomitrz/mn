function u = rrc(f, mi, N, h)
    % Dane: f, mi, brzegi u (są zero), N, h
    % mi (d^2/dx^2 + d^2u/dy^2) = f(x)
    % mi (u(i+1, j) + u(i-1, j) + u(i, j+1) + u(i, j-1) - 4u(i, j)) / h2 = f(x)
    h2 = h^2; % To calculate it once
    % mi = mi(x(i, j))
    get_idx = @(i, j) i + N * (j - 1); % u(i, j) = u(i + N*j)

    A = sparse(N^2, N^2);
    fs = zeros(N^2, 1);

    for i = 1 : N
        for j = 1 : N
            if (i == 1 || j == 1 || i == N || j == N)
                A(get_idx(i, j), get_idx(i, j)) = 1;
                fs(get_idx(i, j)) = 0; % Borders of u are zeros
            else
                A(get_idx(i, j), get_idx(i+1, j)) = 1 * mi(i, j) / h2;
                A(get_idx(i, j), get_idx(i-1, j)) = 1 * mi(i, j) / h2;
                A(get_idx(i, j), get_idx(i, j+1)) = 1 * mi(i, j) / h2;
                A(get_idx(i, j), get_idx(i, j-1)) = 1 * mi(i, j) / h2;
                A(get_idx(i, j), get_idx(i, j)) = -4 * mi(i, j) / h2;
                fs(get_idx(i, j)) = f(i, j);
            end
        end
    end

    u =  A \ fs;
    u = reshape(u, [N, N]);
end
