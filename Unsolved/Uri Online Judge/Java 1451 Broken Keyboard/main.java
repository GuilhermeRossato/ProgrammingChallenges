import java.util.Scanner;
import java.io.IOException;

public class Main {
	public static void main(String[] args) throws IOException {
		Scanner input = new Scanner(System.in);
		while (input.hasNextLine()) {
			String text = input.nextLine();
			if (text.length() == 0)
				break;
			else {
				int cursor = 0;
				String newText = "";
				for (int i = 0; i < text.length(); i++) {
					if (text.charAt(i) == '[') {
						cursor = 0;
					} else if (text.charAt(i) == ']') {
						cursor = newText.length();
					} else if (newText.length() == cursor) {
						newText += text.charAt(i);
						cursor ++;
					} else {
						newText = newText.substring(0, Math.max(cursor,0)) + text.charAt(i) + newText.substring(cursor);
						cursor ++;
					}
				}
				System.out.println(newText);
			}
		}
	}
}