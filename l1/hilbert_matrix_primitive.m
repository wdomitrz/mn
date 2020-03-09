function H = hilbert_matrix_primitive(N)
    H = zeros(N);
    for i = 1:N
    	H(i, :) = [i : i+N-1];
	end
	H = 1 ./ H;
end