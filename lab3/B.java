import java.io.*;
import java.util.*;

public class DSU {
    String fileName = "dsu";

    class Node {
        int number, min, max, count, prev;

        public Node(int number, int min, int max, int count, int prev) {
            this.number = number;
            this.min = min;
            this.max = max;
            this.count = count;
            this.prev = prev;
        }
    }

    Node[] a;

    int get(int u) {
        if (a[u].prev == u) {
            return u;
        }
        int prev = get(a[u].prev);
        if (u != prev && a[u].prev != prev) {
            a[u].prev = prev;
        }
        return prev;
    }

    void union(int u, int v) {
        u = get(u);
        v = get(v);
        if (u != v) {
            if (a[u].count > a[v].count) {
                int l = u;
                u = v;
                v = l;
            }
            a[v].prev = u;
            a[u].count += a[v].count;
            a[u].min = Math.min(a[u].min, a[v].min);
            a[u].max = Math.max(a[u].max, a[v].max);
        }
    }

    public void solve() throws IOException {
        int n = nextInt();
        a = new Node[n];
        for (int i = 0; i < n; i++) {
            a[i] = new Node(i, i + 1, i + 1, 1, i);
        }
        while (true) {
            String s;
            try {
                s = nextToken();
            } catch (NullPointerException e) {
                return;
            }
            if (s.equals("union")) {
                int u = nextInt() - 1;
                int v = nextInt() - 1;
                union(u, v);
            } else {
                int u = nextInt() - 1;
                int cur = get(u);
                out.println(a[cur].min + " " + a[cur].max + " " + a[cur].count);
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
        new DSU().run();
    }

}