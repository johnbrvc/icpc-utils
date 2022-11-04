#include <stdio.h>
#include <stdlib.h>
#define rep(E, F) for (E = 0; E < (F); E++)
#define per(E, F) for (E = (F) - 1; E >= 0; E--)
int get_int()
{
	int r = 0, c = getchar(), s = 1;
	while (c != '-' && c < '0' || c > '9') c = getchar();
	while (c == '-') s *= -1, c = getchar();
	while (c >= '0' && c <= '9') r = r*10 + c - '0', c = getchar();
	return s*r;
}

int inter(char *s)
{
	int i;
	printf("%s\n", s);
	fflush(stdout);
	while (getchar() != ' ');
	if (getchar() == 'G') exit(0);
	return get_int();
}

int main()
{
	char s[32];
	int i, j, r, mx, mxi;
	rep(i, 32) s[i] = '\0';
	mx = -1;
	rep(i, 20)
	{
		s[i] = 'x';
		r = inter(s);
		if (r > mx) mx = r, mxi = i;
	}
	int l = mxi;
	s[l + 1] = '\0';
	rep(i, l + 1)
	{
		mx = -1;
		rep(j, 26)
		{
			s[i] = j + 'a';
			r = inter(s);
			if (r > mx) mx = r, mxi = 'a' + j;
			s[i] = j + 'A';
			r = inter(s);
			if (r > mx) mx = r, mxi = 'A' + j;
		}
		rep(j, 10)
		{
			s[i] = j + '0';
			r = inter(s);
			if (r > mx) mx = r, mxi = '0' + j;
		}
		s[i] = mxi;
	}
	return 0;
}
