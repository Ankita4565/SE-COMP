class MacroProcessor:
    def __init__(self):
        self.mnt = {}
        self.mdt = []

    def pass1(self, input_lines):
        intermediate_code = []
        in_macro_def = False
        current_macro_name = ''
        mdt_index = 0
        for line in input_lines:
            tokens = line.strip().split()
            if not tokens:
                continue
            if tokens[0] == 'MACRO':
                in_macro_def = True
                continue
            if in_macro_def:
                if not current_macro_name:
                    current_macro_name = tokens[0]
                    self.mnt[current_macro_name] = mdt_index
                else:
                    self.mdt.append(line.strip())
                    mdt_index += 1
                if tokens[0] == 'MEND':
                    in_macro_def = False
                    current_macro_name = ''
            else:
                intermediate_code.append(line.strip())
        return intermediate_code

    def pass2(self, intermediate_code):
        output_code = []
        for line in intermediate_code:
            tokens = line.strip().split()
            if not tokens:
                continue
            macro_name = tokens[0]
            if macro_name in self.mnt:
                self.expand_macro(self.mnt[macro_name], tokens[1:], output_code)
            else:
                output_code.append(line.strip())
        return output_code

    def expand_macro(self, mdt_index, args, output_code):
        while self.mdt[mdt_index] != 'MEND':
            line = self.mdt[mdt_index]
            expanded_line = self.replace_args(line, args)
            output_code.append(expanded_line)
            mdt_index += 1

    def replace_args(self, line, args):
        tokens = line.split()
        return ' '.join(args[int(tok[1:]) - 1] if tok.startswith('&') else tok for tok in tokens)

if __name__ == "__main__":
    input_lines = [
        "MACRO",
        "INCR &1, &2",
        "ADD &1",
        "SUB &2",
        "ADD &1",
        "MEND",
        "START",
        "INCR A B",
        "INCR aa bb",
        "END"
    ]

    macro_processor = MacroProcessor()
    intermediate_code = macro_processor.pass1(input_lines)
    output_code = macro_processor.pass2(intermediate_code)

    print("MNT:", macro_processor.mnt)
    print("MDT:", macro_processor.mdt)
    print("Intermediate Code:", intermediate_code)
    print("Output Code:", output_code)
