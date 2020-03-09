function poly_interp_plot(n, f=@(x) 1./(1+x.^2), a=-2, b=2, n_interp=10)
    xs_uniform = a:(b-a)/(n-1):b;
    ys_uniform = f(xs_uniform);
    p_uniform = polyfit(xs_uniform, ys_uniform, n-1);

    is = 1:n;
    xs_chebyshew = (a+b) + ((b-a) / 2) * cos( (2 .* is - 1) * pi ./ (2 * n) );
    ys_chebyshew = f(xs_chebyshew);
    p_chebyshew = polyfit(xs_chebyshew, ys_chebyshew, n-1);

    fplot(f, [a, b]);
    hold on;
    fplot(@(x) polyval(p_uniform, x), [a, b]);
    fplot(@(x) polyval(p_chebyshew, x), [a, b]), legend("f", "poly uniform", "poly chebyshew");
    hold off;
end
