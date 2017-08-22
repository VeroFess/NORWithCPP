#pragma once
class NOR {
private :
	__forceinline static int __stdcall NOR::nor_nor(int a, int b) {
		return ~(a | b);
	}

	__forceinline static int __stdcall NOR::negtive(int i) {
		return nor_add(nor_not(i), 1);
	}

	__forceinline static int __stdcall NOR::getsign(int i) {
		return (i >> 31);
	}

	__forceinline static int __stdcall NOR::bepositive(int i) {
		if (i >> 31) {
			return negtive(i);
		} else {
			return i;
		}
	}

public:
	__forceinline static int __stdcall NOR::nor_not(int a) {
		return nor_nor(a, a);
	}

	__forceinline static int __stdcall NOR::nor_or(int a, int b) {
		return nor_not(nor_nor(a, b));
	}

	__forceinline static int __stdcall NOR::nor_and(int a, int b) {
		return nor_not(nor_or(nor_not(a), nor_not(b)));
	}

	__forceinline static int __stdcall NOR::nor_xor(int a, int b) {
		return nor_or(nor_and(a, nor_not(b)), nor_and(nor_not(a), b));
	}

	__forceinline static int __stdcall NOR::nor_add(int a, int b) {
		if (b == 0) {
			return a;
		}
		int s = nor_xor(a, b);
		int c = nor_and(a, b) << 1;
		return nor_add(s, c);
	}

	__forceinline static int __stdcall NOR::nor_sub(int a, int b) {
		return nor_add(a, negtive(b));
	}

	__forceinline static int __stdcall NOR::nor_mul(int a, int b) {
		bool flag = true;
		if (getsign(a) == getsign(b)) {
			flag = false;
		}
		a = bepositive(a);
		b = bepositive(b);
		int ans = 0;
		while (b) {
			if (nor_and(b, 1)) {
				ans = nor_add(ans, a);
			}
			a = (a << 1);
			b = (b >> 1);
		}

		if (flag) {
			ans = negtive(ans);
		}
		return ans;
	}

	__forceinline static int __stdcall NOR::nor_div(int dividend, int divisor) {
		bool flag = true;
		if (getsign(dividend) == getsign(divisor)) {
			flag = false;
		}

		unsigned int x = bepositive(dividend);
		unsigned int y = bepositive(divisor);

		int ans = 0;
		int i = 31;
		while (i >= 0) {
			if ((x >> i) >= y) {
				ans = nor_add(ans, (1 << i));
				x = nor_sub(x, (y << i));
			}
			i = nor_sub(i, 1);
		}
		if (flag) {
			ans = negtive(ans);
		}
		return ans;
	}
};

