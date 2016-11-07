import java.util.Scanner;
import java.io.IOException;

public class Main {
    public static void main(String[] args) throws IOException {
		Scanner input = new Scanner(System.in);
		String maxWord = "";
		int maxLength = Integer.MIN_VALUE;
		while (input.hasNextLine()) {
			String text = input.nextLine();
			if ((text.length() > 0) && (text.charAt(0) == '0')) {
				break;
			} else {
				boolean newLine = false;
				boolean first = true;
				for (String word: text.split(" ")) {
					int now = word.length();
					if (now > 0) {
						newLine = true;
						if (!first)
							System.out.print("-");
						else
							first = false;
						System.out.print(now);
						if (now >= maxLength) {
							maxLength = now;
							maxWord = word;
						}
					}
				}
				if (newLine)
					System.out.println();
			}
		}
		System.out.println();
		System.out.println("The biggest word: "+maxWord);
    }
}