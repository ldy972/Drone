#!/usr/bin/env python2
##################################################
# GNU Radio Python Flow Graph
# Title: Top Block
# Generated: Mon Jan 18 16:38:22 2016
##################################################

from gnuradio import blocks
from gnuradio import eng_notation
from gnuradio import gr
from gnuradio.eng_option import eng_option
from gnuradio.filter import firdes
from optparse import OptionParser


class top_block(gr.top_block):

    def __init__(self):
        gr.top_block.__init__(self, "Top Block")

        ##################################################
        # Blocks
        ##################################################
        self.blocks_uchar_to_float_1 = blocks.uchar_to_float()
        self.blocks_uchar_to_float_0 = blocks.uchar_to_float()
        self.blocks_multiply_const_vxx_1 = blocks.multiply_const_vff((8e-3, ))
        self.blocks_multiply_const_vxx_0 = blocks.multiply_const_vff((8e-3, ))
        self.blocks_float_to_complex_0 = blocks.float_to_complex(1)
        self.blocks_file_source_0 = blocks.file_source(gr.sizeof_char*1, "/home/yann/Documents/INSA/5SEC/Drone/Dongle/script_grc/capture.bin", True)
        self.blocks_file_sink_0 = blocks.file_sink(gr.sizeof_gr_complex*1, "/home/yann/Documents/INSA/5SEC/Drone/Dongle/script_grc/capture.c", False)
        self.blocks_file_sink_0.set_unbuffered(False)
        self.blocks_deinterleave_0 = blocks.deinterleave(gr.sizeof_char*1, 1)
        self.blocks_add_const_vxx_1 = blocks.add_const_vff((-127, ))
        self.blocks_add_const_vxx_0 = blocks.add_const_vff((-127, ))

        ##################################################
        # Connections
        ##################################################
        self.connect((self.blocks_add_const_vxx_0, 0), (self.blocks_multiply_const_vxx_0, 0))    
        self.connect((self.blocks_add_const_vxx_1, 0), (self.blocks_multiply_const_vxx_1, 0))    
        self.connect((self.blocks_deinterleave_0, 0), (self.blocks_uchar_to_float_0, 0))    
        self.connect((self.blocks_deinterleave_0, 1), (self.blocks_uchar_to_float_1, 0))    
        self.connect((self.blocks_file_source_0, 0), (self.blocks_deinterleave_0, 0))    
        self.connect((self.blocks_float_to_complex_0, 0), (self.blocks_file_sink_0, 0))    
        self.connect((self.blocks_multiply_const_vxx_0, 0), (self.blocks_float_to_complex_0, 0))    
        self.connect((self.blocks_multiply_const_vxx_1, 0), (self.blocks_float_to_complex_0, 1))    
        self.connect((self.blocks_uchar_to_float_0, 0), (self.blocks_add_const_vxx_0, 0))    
        self.connect((self.blocks_uchar_to_float_1, 0), (self.blocks_add_const_vxx_1, 0))    



if __name__ == '__main__':
    parser = OptionParser(option_class=eng_option, usage="%prog: [options]")
    (options, args) = parser.parse_args()
    tb = top_block()
    tb.start()
    try:
        raw_input('Press Enter to quit: ')
    except EOFError:
        pass
    tb.stop()
    tb.wait()
