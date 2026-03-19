package nowcoder.bishi;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Scanner;

public class Main1 {

    public static void main(String[] var0) {
        Scanner sc = new Scanner(System.in);

        int q = sc.nextInt();

        List<Integer> list = new ArrayList<>();

        for (int i = 0; i < q; ++i) {
            int op1 = sc.nextInt();
            if (op1 == 1 || op1 == 3) {
                int op2 = sc.nextInt();
                if (op1 == 1) {
                    list.add(op2);
                }
                if (op1 == 3) {
                    System.out.println(list.get(op2));
                }
            }
            if (op1 == 4) {
                int op2 = sc.nextInt(), op3 = sc.nextInt();

                list.add(op2 + 1, op3);
            }
            if (op1 == 2) {
                list.remove(list.size() - 1);
            }
            if (op1 == 5) {
                Collections.sort(list);
            }
            if (op1 == 6) {
                list.sort(Collections.reverseOrder());
            }
            if (op1 == 7) {
                System.out.println(list.size());
            }
            if (op1 == 8) {
                for (int x : list) {
                    System.out.print(x + " ");
                }
                System.out.println();
            }
        }

        sc.close();
    }
}
