% tools.SQUARE_ROOT was generated on Fri Jan 24, 2014 01:17:24 AM by xcpp 
% 
%     Compute the square root of a number using Newton's method.
%     This function will print to stdout the amount of time it took to
%     execute.
% 
%     parameters:
% 
%       `x`: the input to the square root function.
%       `x0`: initial guess.
%       `iter`: number of iterations.
%     
function varargout = square_root(x, x0, iter, varargin)
    tdump = excentury.dump.textdumper;
    tdump.dump(x, 'x', {'R', '8'});
    tdump.dump(x0, 'x0', {'R', '8'});
    tdump.dump(iter, 'iter', {'I', '4'});
    in_str = tdump.close;
    len_in = length(in_str);
    [~, out_str] = tools.square_root_mex(len_in, in_str);
    [val, order] = excentury.load.textparser(out_str).parse;
    if isempty(varargin)
        nout = length(order);
        varargout = cell(1, nout);
        for num=1:nout;
            varargout{num} = val(order{num});
        end
    else
        varargout{1} = val;
    end
end
