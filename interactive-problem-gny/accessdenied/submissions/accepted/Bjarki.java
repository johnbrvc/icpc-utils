import java.io.*;
import java.util.*;

public class Bjarki {
    static long time(int correct) {
        int cnt = 0;
        cnt += 3; // pwd1.Length != pwd2.Length
        cnt += 1; // if branch

        cnt += 1; // i = 0
        for (int i = 0; i < correct; i++) {
            cnt += 3; // i < pwd1.Length
            cnt += 1; // for branch

            cnt += 3; // pwd1[i] != pwd2[i]
            cnt += 1; // if branch

            cnt += 1; // i++
        }

        cnt += 3; // i < pwd1.Length
        cnt += 1; // for branch

        cnt += 3; // pwd1[i] != pwd2[i]
        cnt += 1; // if branch

        cnt += 1; // return false
        return cnt;
    }

    static long getActual(Scanner in) {
        String ans = in.nextLine();
        if (ans.startsWith("ACCESS GRANTED")) {
            System.exit(0);
        }
        return Long.valueOf(ans.split("\\(")[1].split(" ")[0]);
    }

    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(System.in);
        int length = 1;
        while (true) {
            String s = "";
            for (int i = 0; i < length; i++) {
                s += "x";
            }
            System.out.println(s);
            if (getActual(in) != 5) {
                break;
            }
            length++;
        }
        String s = "";
        for (int i = 0; i < length; i++) {
            s += "x";
        }
        String alpha = "";
        for (int i = 0; i < 26; i++) {
            alpha += (char)((int)'a' + i);
            alpha += (char)((int)'A' + i);
        }
        for (int i = 0; i < 10; i++) {
            alpha += (char)((int)'0' + i);
        }
        for (int at = 0; at < length; at++) {
            for (int i = 0; i < alpha.length(); i++) {
                s = s.substring(0, at) + alpha.charAt(i) + s.substring(at+1);
                System.out.println(s);
                long actual = getActual(in);
                if (actual > time(at)) {
                    break;
                } else if (actual != time(at)) {
                    throw new Exception("Reported time is wrong");
                }
            }
        }
    }
}
