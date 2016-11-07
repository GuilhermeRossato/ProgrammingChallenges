import java.util.Scanner;
import java.io.IOException;
import java.util.Locale;
import java.text.NumberFormat;

public class Main {
	static int divs[] = {10000, 5000, 2000, 1000, 500, 200, 100, 50, 25, 10, 5, 1};
	public static void main(String[] args) throws IOException {
		NumberFormat dt = NumberFormat.getInstance(Locale.US);
		dt.setMinimumFractionDigits(2);
		dt.setMaximumFractionDigits(2);
		dt.setMinimumIntegerDigits(1);
		Scanner input = new Scanner(System.in).useLocale(Locale.US);
		int value = (int) Math.round(input.nextDouble()*100);
		int counts[] = new int[12];
		for (int i=0;i<12;i++) {
			while (value >= divs[i]) {
				value -= divs[i];
				counts[i]++;
			}
		}
		System.out.println("NOTAS:");
		for (int i=0;i<6;i++) {
			System.out.println(counts[i]+" nota(s) de R$ "+dt.format((double)divs[i]/100));
		}
		System.out.println("MOEDAS:");
		for (int i=6;i<12;i++) {
			System.out.println(counts[i]+" moeda(s) de R$ "+dt.format((double)divs[i]/100));
		}
	}
}