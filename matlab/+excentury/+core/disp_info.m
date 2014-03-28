function str = disp_info(info)
% excentury.core.DISP_INFO: Display an information from object.
%
% Given the output obtained from excentury.core.get_info we can
% pass it to this function to display it.
%
    switch info{1}
        case 'S'
            str = sprintf('[S %s]', info{2});
        case 'T'
            str = sprintf('[T %s]', excentury.disp_info(info{2}));
        case 'W'
            str = sprintf('[W]');
        otherwise
            str = sprintf('[%s %s]', info{1}, info{2});
    end
end
