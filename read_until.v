import os

fn main() {
	if os.args.len != 2 {
		eprintln('Usage: read_until <sequence>')
		exit(1)
	}

	sequence := os.args[1]
	mut buffer := []u8{}
	mut b := u8(0)

	for {
		b = u8(C.getchar())
		if int(b) == C.EOF {
			break
		}
		buffer << b
		if buffer.len >= sequence.len && buffer#[-sequence.len..].bytestr() == sequence {
			break
		}
	}

	print(buffer.bytestr())
}
