% arma.EX1 generated on Tue Apr 15, 2014 12:54:17 PM by xcpp
% 
%     Armadillo example 2: Computes the determinant and inverse of a
%     matrix.
% 
%     parameters:
% 
%       `A`: input matrix
%     
function varargout = ex1(A, varargin)
    tdump = excentury.dump.textdumper;
    tdump.dump(A, 'A', {'T', {'R', '8'}});
    in_str = tdump.close;
    len_in = length(in_str);
    [~, out_str] = arma.ex1_mex(len_in, in_str);
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
