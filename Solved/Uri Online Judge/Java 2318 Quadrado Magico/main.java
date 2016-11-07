import java.util.Scanner;
import java.io.IOException;

public class Main {
	
	public static int put(int p, int a, int b, int c) {
		return (p!=0)?p:((a!=0 && b!= 0 && c != 0)?a+b+c:0);
	}
	
	public static int cPut(int p, int a, int b, int c, int d, int g) {
		if (a != 0)
			return a;
		else if (b != 0 && c != 0)
			return (p-b-c);
		else if (d != 0 && g != 0)
			return (p-d-g);
		else
			return 0;
	}
	
	public static void main(String[] args) throws IOException {
		Scanner input = new Scanner(System.in);
		int a,b,c,d,e,f,g,h,i;
		a = input.nextInt();
		b = input.nextInt();
		c = input.nextInt();
		d = input.nextInt();
		e = input.nextInt();
		f = input.nextInt();
		g = input.nextInt();
		h = input.nextInt();
		i = input.nextInt();
		int p = 0; // Find Special Sum
		p = put(put(put(put(put(put(put(put(p,c,e,g),a,e,i),c,f,i),b,e,h),a,d,g),g,h,i),d,e,f),a,b,c);
		if (p==0) {
			if (a == 0) {
				a = (g+h+d+f-c-b)/2;
				p = a+b+c;
				e = p-d-f;
				i = p-g-h;
			} else {
				c = (i+h+f+d-a-b)/2;
				p = a+b+c;
				e = p-d-f;
				g = p-i-h;
			}
		}
		a = cPut(p,a,b,c,d,g); // Line 1
		if (a == 0 && e != 0 && i != 0) a = p-e-i;
		b = cPut(p,b,c,a,e,h);
		c = cPut(p,c,a,b,f,i);
		if (c == 0 && e != 0 && g != 0) c = p-e-g;
		d = cPut(p,d,e,f,a,g); // Line 2
		e = cPut(p,e,d,f,b,h);
		if (e == 0 && a != 0 && i != 0) e = p-a-i;
		else if (e == 0 && c != 0 && g != 0) e = p-c-g;
		f = cPut(p,f,d,e,c,i);
		g = cPut(p,g,h,i,a,d); // Line 3
		if (g == 0 && e != 0 && c != 0) c = p-e-c;
		h = cPut(p,h,i,g,b,e);
		i = cPut(p,i,g,h,c,f);
		// Redo some to make sure everything is okay
		d = cPut(p,d,e,f,a,g);
		b = cPut(p,b,c,a,e,h);
		f = cPut(p,f,d,e,c,i);
		h = cPut(p,h,i,g,b,e);
		
		System.out.println(a+" "+b+" "+c);
		System.out.println(d+" "+e+" "+f);
		System.out.println(g+" "+h+" "+i);
	}
}