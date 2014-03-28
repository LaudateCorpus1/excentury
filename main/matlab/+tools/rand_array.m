% tools.RAND_ARRAY was generated on Fri Jan 24, 2014 01:17:25 AM by xcpp 
% 
%     Get an array of random numbers from a uniform distribution.
% 
%     parameters:
% 
%       `n`: amount of random numbers.
%       `mean`: the mean of the distribution.
%       `std`: the standard deviation of the distribution.
%     
function varargout = rand_array(n, mean, std, varargin)
    tdump = excentury.dump.textdumper;
    tdump.dump(n, 'n', {'I', '4'});
    tdump.dump(mean, 'mean', {'R', '8'});
    tdump.dump(std, 'std', {'R', '8'});
    in_str = tdump.close;
    len_in = length(in_str);
    [~, out_str] = tools.rand_array_mex(len_in, in_str);
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
