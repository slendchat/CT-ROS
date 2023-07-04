.global memzero     // x0 addr x1 length
memzero:
	str xzr, [x0], #8
	subs x1,x1,#8
    b.gt memzero
	ret