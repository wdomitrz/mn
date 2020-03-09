function [v_max, v_max2, v_near]=find_eigenvectors_of_M(n, near_what=2.3, K=1000, plt=1, all_eigenvectors=0)
    %precompute:
    e = ones(n, 1);
    A = spdiags([e -2*e e],-1:1,n,n);;
    I = speye(n);
    Z = sparse(n, n);

    M = [Z , I ; A, Z];

    if all_eigenvectors == 0
        M_max = M;
        v_max = rand(2 * n, 1);
        for i = 1:K
            v_max = M_max * v_max;
            v_max /= norm(v_max);
        end

        M_max2 = M - norm(M * v_max) * v_max * v_max';
        v_max2 = rand(2 * n, 1);
        for i = 1:K
            v_max2 = M_max2 * v_max2;
            v_max2 /= norm(v_max2);
        end

        M_near = M - near_what * speye(2 * n);
        v_near = rand(2 * n, 1);
        for i = 1:K
            v_near = M \ v_near;
            v_near /= norm(v_near);
        end
        v_near = M * v_near;
        v_near /= norm(v_near);


        if plt == 1
            hold on;
            ys = 1 : 2 * n;
            plot(ys, v_max, ys, v_max2, ys, v_near), legend("v max", "v max2", "v near");
            hold off;
        end
    else
        v = rand(2 * n, 2 * n);
        [V, D] = eig(M);
        for j = 1: 2 * n
            for i = 1:K
                v(:, j) = M * v(:, j);
                v(:, j) /= norm(v(:, j));
            end
            M -= norm(M * v(:, j)) * v(:, j) * v(:, j)';
        end

        % v = V;
        if plt == 1
            hold on;
            ys = 1 : 2 * n;
            for j = 1: 2 * n
                plot(ys, v(:, j));
            end
            hold off;
        end
    end
end
