#!/usr/bin/python
# encoding=utf-8

import os,sys,multiprocessing,argparse,logging,signal

class UDTProcess(multiprocessing.Process):
    def run(self):
        a = 0
        while True:
            a += 1

def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument('-p', '--parallel', required=True, type=int, dest='parallel')
    return parser.parse_args()

def exit_signal_handler(sig=None, frame=None):
    logging.error('process[{}] got signal[{}]; ready to exit'.format(multiprocessing.current_process().pid, sig))
    while multiprocessing.active_children():
        for p in multiprocessing.active_children():
            os.kill(p.pid, signal.SIGKILL)

if __name__ == '__main__':
    signal.signal(signal.SIGINT, exit_signal_handler)
    signal.signal(signal.SIGTERM, exit_signal_handler)
    logging.basicConfig(
        format='%(asctime)s-%(levelname)s-%(filename)s-%(lineno)d; %(message)s',
        level=logging.INFO)
    arguments = parse_args()
    for i in range(arguments.parallel):
        p = UDTProcess()
        p.start()
