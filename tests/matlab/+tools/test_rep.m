% tools.TEST_REP was generated on Fri Jan 24, 2014 01:17:26 AM by xcpp 
% 
%     This function will do useless computation for the sake of
%     testing the reporter object which will print messages to
%     stdout.    
function varargout = test_rep(varargin)
    tdump = excentury.dump.textdumper;
    in_str = tdump.close;
    len_in = length(in_str);
    [~, out_str] = tools.test_rep_mex(len_in, in_str);
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
