function H = hilbert_matrix(N)
    H = 1 ./ ([1:N]' + [0:(N-1)]);
end