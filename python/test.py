

import argparse

if __name__ == '__main__':
	parser = argparse.ArgumentParser(description='Process integers.')
    # basic params
    parser.add_argument('--model_path', type=str, default='./yolov5s.rknn', help='model path, .rknn file')
    parser.add_argument('--input_source', type=str, required=True, help='input image source, if use usb camera, input 0')
    parser.add_argument('--usb_camera', action='store_true', help='use usb camera')
    parser.add_argument('--thread_num', type=int, default=8, help='thread number')
    args = parser.parse_args()

	print(args.thread_num)
