% util.SCALE was generated on Sat Jan 04, 2014 08:39:28 PM by xcpp 
% 
%     Scalar multiplication.
% 
%     parameters:
% 
%       `v`: the vector to multiply. 
%       `alpha`: the scalar.
%     
function varargout = scale(v, alpha, varargin)
    tdump = excentury.dump.textdumper;
    tdump.dump(v, 'v', {'T', {'R', '8'}});
    tdump.dump(alpha, 'alpha', {'R', '8'});
    in_str = tdump.close;
    len_in = length(in_str);
    [~, out_str] = util.scale_mex(len_in, in_str);
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
