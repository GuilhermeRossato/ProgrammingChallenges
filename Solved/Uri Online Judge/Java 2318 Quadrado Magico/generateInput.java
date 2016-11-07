import java.util.Scanner;
import java.io.IOException;
import java.lang.Math;
import java.io.PrintWriter;
import java.util.Random;

public class generateInput {
	
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
	
	public static boolean allOk(int p, int a, int b, int c) {
		return (p==a+b+c && a > 0 && b > 0 && c > 0);
	}
	
	
	public static void main(String[] args) throws IOException {
		Scanner input = new Scanner(System.in);
		Random rand = new Random(System.currentTimeMillis());
		double limit = 10;
		for (int n = 0; n < 100; n++) {
			limit = 10+(10000-10)*(n/100);
			try{
				int a=0,b=0,c=0,d=0,e=0,f=0,g=0,h=0,i=0,p=0;
				a = (int) Math.round(rand.nextDouble()*limit);
				for (int t=0;t<300000;t++) {
					e = (int) Math.round(rand.nextDouble()*limit);
					i = (int) Math.round(rand.nextDouble()*limit);
					g = (int) Math.round(rand.nextDouble()*limit);
					p = a+e+i;
					c = p-e-g;
					h = p-g-i;
					b = p-a-c;
					d = p-a-g;
					f = p-e-d;
					if (allOk(p,a,b,c)&& // Lines
						allOk(p,d,e,f)&& 
						allOk(p,g,h,i)&&
						allOk(p,a,d,g)&& // Columns
						allOk(p,b,e,h)&&
						allOk(p,c,f,i)&&
						allOk(p,a,e,i)&& // Diagonals
						allOk(p,g,e,c)) {
					break;
					}
				}
				if (
				allOk(p,a,b,c)&& // Lines
				allOk(p,d,e,f)&& 
				allOk(p,g,h,i)&&
				allOk(p,a,d,g)&& // Columns
				allOk(p,b,e,h)&&
				allOk(p,c,f,i)&&
				allOk(p,a,e,i)&& // Diagonals
				allOk(p,g,e,c)
				) {
					PrintWriter writer = new PrintWriter("Input/file"+n+".txt", "UTF-8");
					writer.println(a+" "+b+" "+c);
					writer.println(d+" "+e+" "+f);
					writer.println(g+" "+h+" "+i);
					writer.close();
					System.out.println(" --------------------- Got "+n+" --------------------- ");
				} else {
					System.out.println("Rejected "+p);
					System.out.println("\t"+a+"\t"+b+"\t"+c);
					System.out.println("\t"+d+"\t"+e+"\t"+f);
					System.out.println("\t"+g+"\t"+h+"\t"+i);
				}
			} catch (Exception ex) {
			   // do something
			}
		}
		System.out.println("Finished");
	}
}