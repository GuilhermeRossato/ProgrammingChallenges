import java.util.Scanner;
import java.io.IOException;
import java.util.Locale;
import java.text.NumberFormat;

public class Main {
	
	public static void main(String[] args) throws IOException {
		NumberFormat dt = NumberFormat.getInstance(Locale.US);
		dt.setMinimumFractionDigits(1);
		dt.setMaximumFractionDigits(1);
		dt.setMinimumIntegerDigits(1);
		Scanner input = new Scanner(System.in).useLocale(Locale.US);
		
		double n1 = input.nextDouble();
		double n2 = input.nextDouble();
		double n3 = input.nextDouble();
		double n4 = input.nextDouble();
		double media = (n1*2+n2*3+n3*4+n4)/(2+3+4+1);
		
		System.out.println("Media: "+dt.format(media));
		if (media >= 7)
			System.out.println("Aluno aprovado.");
		else if (media < 5) {
			System.out.println("Aluno reprovado.");
		} else {
			System.out.println("Aluno em exame.");
			double ex = input.nextDouble();
			System.out.println("Nota do exame: "+dt.format(ex));
			media = (media + ex)/2;
			if (media >= 5)
				System.out.println("Aluno aprovado.");
			else
				System.out.println("Aluno reprovado.");
			System.out.println("Media final: "+dt.format(media));
		}
	}
}