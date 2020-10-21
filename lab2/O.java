import java.io.*;
import java.util.*;

public class O {
    String fileName = "";

    int n;
    int[] a = new int[10];

    class Pair {
        int first, second;

        public Pair(int first, int second) {
            this.first = first;
            this.second = second;
        }
    }

    ArrayList<Pair> ans = new ArrayList<>();

    boolean isSorted(int l, int r) {
        for (int i = l + 1; i < r; i++) {
            if (a[i] < a[i - 1]) {
                return false;
            }
        }
        return true;
    }

    void build(int l, int r) {
        if (r - l == 2) {
            return;
        }
        if (!isSorted(l + 1, r)) {
            build(l + 1, r);
            if (a[l] == 0) {
                for (int i = r - 1; i > l; i--) {
                    ans.add(new Pair(l, i));
                }
            } else {
                for (int i = l; i < r - 1; i++) {
                    ans.add(new Pair(i, i + 1));
                }
            }
        } else {
            build(l, r - 1);
            if (a[r - 1] == 0) {
                for (int i = r - 1; i > l; i--) {
                    ans.add(new Pair(i, i - 1));
                }
            } else {
                for (int i = l; i < r - 1; i++) {
                    ans.add(new Pair(r - 1, i));
                }
            }
        }
    }

    public void solve() throws IOException {
        while ((n = nextInt()) != 0) {
            for (int i = 0; i < n; i++) {
                a[i] = nextInt();
            }
            if (isSorted(0, n)) {
                out.println(-1);
            } else {
                ans = new ArrayList<>();
                build(0, n);
                out.println(ans.size());
                for (Pair pair : ans) {
                    out.println((pair.first + 1) + " " + (pair.second + 1));
                }
            }
        }
    }

    public void run() {
        try {
            if ("".equals(fileName)) {
                br = new BufferedReader(new InputStreamReader(System.in));
                out = new PrintWriter(System.out);
            } else {
                br = new BufferedReader(new FileReader(fileName + ".in"));
                out = new PrintWriter(fileName + ".out");
            }
            solve();

            out.close();
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(1);
        }
    }

    BufferedReader br;
    StringTokenizer in;
    PrintWriter out;

    public String nextToken() throws IOException {
        while (in == null || !in.hasMoreTokens()) {
            in = new StringTokenizer(br.readLine());
        }
        return in.nextToken();
    }

    public int nextInt() throws IOException {
        return Integer.parseInt(nextToken());
    }

    public double nextDouble() throws IOException {
        return Double.parseDouble(nextToken());
    }

    public long nextLong() throws IOException {
        return Long.parseLong(nextToken());
    }

    public static void main(String[] args) throws IOException {
        Locale.setDefault(Locale.US);
        new O().run();
    }

}