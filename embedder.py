
import os.path
import argparse

def main():
	parser = argparse.ArgumentParser(
		description='Creates embeddable C++ source files from any resource file.')
	parser.add_argument(
		'resources', type=str, nargs='+',
		help='The resources to embed.')
	parser.add_argument(
		'-o', '--output', type=str, default='./',
		help='The folder to dump generated soruce files to.')
	parser.add_argument(
		'-f', '--file', type=str, default='resources.cpp',
		help='The file that will contain the actual resource data.')

	args = parser.parse_args()
	

	outputcpp = os.path.join(args.output, args.file);
	with open(outputcpp, 'w') as resfd:
		resfd.write('#include <cstdint>\n\n')

		for file in args.resources:
			basename = os.path.basename(file)\
				.replace(' ', '_').replace('-', '_').replace('.', '_')
			
			# TODO: proper error messages when the file does not exist
			# the standard python ones are enough for now
			with open(file, 'rb') as fd:
				data = bytearray(fd.read())

			outputhpp = os.path.join(args.output, basename + '.hpp');
			with open(outputhpp, 'w') as fd:
				fd.write(
					'#include <cstdint>\n\n' +
					'/* {}, {} bytes */\n'.format(file, len(data)) +
					'extern uint8_t _{}[];\n'.format(basename) +
					'const uint8_t (&{0})[] = _{0};\n\n'.format(basename)
					)
				fd.write(
					'extern size_t _{}_size;\n'.format(basename) +
					'const size_t& {0}_size = _{0}_size;\n'.format(basename)
					)

			
			resfd.write(
				'/* {}, {} bytes */\n'.format(file, len(data)) +
				'uint8_t _{}[] =\n'.format(basename) + '{'
				)

			line = ''
			for i in data:
				num = '{},'.format(i)
				if len(line) + len(num) < 100:
					line += num
				else:
					resfd.write(line + '\n')
					line = num

			resfd.write(line[:-1] + '\n')
			resfd.write('};\n')

			resfd.write(
				'size_t _{0}_size = sizeof(_{0})/sizeof(uint8_t);\n\n'.format(basename)
				)

			print(outputhpp)

if __name__ == '__main__':
	main()
