default: rows shiftc

rows:
	$(CC) rows.c -o rows

shiftc:
	$(CC) shiftchr.c -o shiftc
