function plot_hilbert_cond(N)
	for i = 1 : N
		x(i) = i;
		y(i) = cond(hilbert_matrix(i));
	end
	plot(x, y);
end