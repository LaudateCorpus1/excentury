"""Load Text

Function designed to read an excentury text file.

"""

import re
import numpy as np
from collections import OrderedDict
from excentury.core import LOAD_DEFS, XCStruct

RE_NEXT = re.compile(r'.*?[ \n]')


class TextParser(object):
    """Object designed to parse a text file with the excentury
    format."""

    def __init__(self, txt):
        self.text = txt
        self.caret = 0
        self.read = {
            'C1': self.get_char,
            'I1': self.get_int,
            'N1': self.get_int,
            'I2': self.get_int,
            'I4': self.get_int,
            'I8': self.get_long,
            'N2': self.get_int,
            'N4': self.get_int,
            'N8': self.get_long,
            'R4': self.get_float,
            'R8': self.get_float
        }

    def get_char(self):
        """Read a single character. """
        ret = self.text[self.caret]
        self.caret += 2
        return ret

    def get_str(self):
        """Read a string until the next space character. """
        match = RE_NEXT.search(self.text, self.caret)
        if match:
            ret = self.text[self.caret:match.end(0)-1]
            self.caret = match.end(0)
        else:
            ret = self.text[self.caret:]
            self.caret = len(self.text)
        return ret

    def get_int(self):
        """Read an integer. """
        return int(self.get_str())

    def get_long(self):
        """Read a long integer. """
        return long(self.get_str())

    def get_float(self):
        """Read a float. """
        return float(self.get_str())

    def get_info(self):
        """Read the info of a variable. """
        tmp_type = self.get_char()
        if tmp_type == 'S':
            info = [tmp_type, self.get_str()]
        elif tmp_type == 'T':
            info = [tmp_type, self.get_info()]
        elif tmp_type == 'W':
            info = ['W']
        else:
            info = [tmp_type, self.get_char()]
        return info

    def get_data(self, defs, info):
        """Read the variable data. """
        if info[0] == 'S':
            if info[1] in LOAD_DEFS:
                return LOAD_DEFS[info[1]](self, defs)
            else:
                ans = XCStruct(info[1], defs[info[1]])
                for item in defs[info[1]]:
                    ans.__setattr__(item[0], self.get_data(defs, item[1]))
                return ans
        elif info[0] == 'T':
            return self.get_tensor_data(defs, info)
        elif info[0] == 'W':
            total = self.get_int()
            begin = self.caret
            self.caret += total+1
            return self.text[begin:begin+total]
        else:
            return self.read[info[0]+info[1]]()

    def get_tensor_data(self, defs, info):
        """Read a the tensor data. """
        rm_ = self.get_int()
        ndim = self.get_int()
        dim = range(ndim)
        total = 1
        for i in xrange(ndim):
            dim[i] = self.get_int()
            total *= dim[i]
        sub = info[1]
        ans = range(total)
        if sub[0] in ['C', 'I', 'N', 'R']:
            for i in xrange(total):
                ans[i] = self.read[sub[0]+sub[1]]()
        else:
            for i in xrange(total):
                ans[i] = self.get_data(defs, sub)
        ans = np.array(ans)
        new_dim = range(len(dim)+len(ans.shape)-1)
        new_dim[0:len(dim)] = dim
        if len(dim) < len(new_dim):
            new_dim[len(dim):] = ans.shape[1:]
        if rm_ == 1:
            return ans.reshape(new_dim, order='C')
        else:
            return ans.reshape(new_dim, order='F')

    def read_header(self):
        """Read the definitions and the number of objects the file
        contains. """
        defs = {}
        ndefs = self.get_int()
        for _ in xrange(ndefs):
            name = self.get_str()
            defs[name] = []
            while self.text[self.caret] != '\n':
                defs[name].append([self.get_str(), self.get_info()])
            self.caret += 1
        nvars = self.get_int()
        return nvars, defs

    def parse(self):
        """Return a dictionary with the objects contained in the
        file. """
        var = OrderedDict()
        nvars, defs = self.read_header()
        for _ in xrange(nvars):
            name = self.get_str()
            info = self.get_info()
            var[name] = self.get_data(defs, info)
            self.caret += 1
        return var

    def parse_info(self):
        """Return a dictionary with the objects contained in the
        file. """
        var = OrderedDict()
        nvars, defs = self.read_header()
        for _ in xrange(nvars):
            name = self.get_str()
            var[name] = self.get_info()
            self.get_data(defs, var[name])
            self.caret += 1
        return var, defs
