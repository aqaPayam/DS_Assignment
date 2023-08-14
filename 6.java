import java.util.Scanner;


public class Main {
    static long p = 29791;
    static long m = 1000009;
    static long[] powers = new long[500010];

    static long pPower(int x) {
        if (powers[x] != 0)
            return powers[x];
        powers[x] = power(p, x);
        return powers[x];
    }

    static long power(long a, long b) {
        long res = 1;
        a = a % m;
        if (a == 0) return 0;
        while (b > 0) {
            if ((b & 1) == 1)
                res = (res * a) % m;
            b = b >> 1;
            a = (a * a) % m;
        }
        return res;
    }

    static public void main(String[] args) {
        StringBuilder result = new StringBuilder();
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        int k = scanner.nextInt();
        scanner.nextLine();
        SegmentTree[] strings = new SegmentTree[n];
        for (int i = 0; i < n; i++) {
            long power = 1;
            String s = scanner.nextLine();
            char[] c = s.toCharArray();
            long[] res = new long[c.length];
            for (int j = 0; j < c.length; j++) {
                res[j] = ((int) c[j] - (int) 'A' + 1) % m * power % m;
                power *= p;
                power %= m;
            }
            strings[i] = new SegmentTree(res);
        }
        for (int i = 0; i < k; i++) {
            int a = scanner.nextInt();
            if (a == 1) {
                int stringIndex = scanner.nextInt();
                int charIndex = scanner.nextInt();
                int chr = scanner.next().charAt(0);
                stringIndex--;
                charIndex--;
                chr = chr - (int) 'A' + 1;
                chr %= m;
                strings[stringIndex].updateTreeNode(charIndex, chr * pPower(charIndex) % m);
            } else {
                int s1 = scanner.nextInt() - 1;
                int s2 = scanner.nextInt() - 1;
                int c11 = scanner.nextInt() - 1;
                int c21 = scanner.nextInt() - 1;
                int length = scanner.nextInt();
                int c12 = c11 + length - 1;
                int c22 = c21 + length - 1;
                long hash1 = strings[s1].query(c11, c12) % m;
                long hash2 = strings[s2].query(c21, c22) % m;
                if (c11 > c21)
                    hash2 = hash2 * pPower(c11 - c21) % m;
                if (c11 < c21)
                    hash1 = hash1 * pPower(c21 - c11) % m;
                if (hash1 == hash2)
                    result.append("YES\n");
                else
                    result.append("NO\n");
            }
        }
        System.out.println(result);
    }
}

class SegmentTree {
    private final int n;
    private final long[] tree;

    public SegmentTree(long[] arr) {
        n = arr.length;
        tree = new long[2 * n];
        build(arr);
    }

    private void build(long[] arr) {


        if (n >= 0) System.arraycopy(arr, 0, tree, n, n);


        for (int i = n - 1; i > 0; --i)
            tree[i] = (tree[i << 1] + tree[i << 1 | 1]) % Main.m;
    }


    public void updateTreeNode(int p, long value) {

        tree[p + n] = value;
        p = p + n;

        for (int i = p; i > 1; i >>= 1)
            tree[i >> 1] = (tree[i] + tree[i ^ 1]) % Main.m;
    }


    public int query(int l, int r) {
        r++;
        int res = 0;

        for (l += n, r += n; l < r;
             l >>= 1, r >>= 1) {
            if ((l & 1) > 0)
                res += tree[l++];

            if ((r & 1) > 0)
                res += tree[--r];
            res %= Main.m;
        }

        return res;
    }


}
