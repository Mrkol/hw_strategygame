
import os.path
import argparse

def main():
	parser = argparse.ArgumentParser(description='Process some integers.')
	parser.add_argument(
		'resources', type=str, nargs='+',
		help='The resources to embed')
	parser.add_argument(
		'-o', '--output', type=str, default='./',
		help='The folder to dump generated headers to.')

	args = parser.parse_args()
	
	for file in args.resources:
		basename = os.path.basename(file).replace(' ', '_').replace('-', '_').replace('.', '_')
		
		# TODO: proper error messages when the file does not exist
		# the standard python ones are enough for now
		with open(file, 'rb') as fd:
			data = bytearray(fd.read())

		outputfile = os.path.join(args.output, basename + '.h');
		with open(outputfile, 'w') as fd:
			fd.write('#include <cstdint>\n')
			fd.write('/* {}, {} bytes */\n'.format(file, len(data)))
			fd.write('const uint8_t {}[] =\n'.format(basename) + '{')

			line = '' 
			for i in data:
				num = '{},'.format(i)
				if len(line) + len(num) < 100:
					line += num
				else:
					fd.write(line + '\n')
					line = num

			fd.write(line[:-1] + '\n')
			fd.write('};\n')

		print(outputfile)

if __name__ == '__main__':
	main()
