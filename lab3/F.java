import java.io.*;
import java.util.*;

public class F {
    String fileName = "";

    class Node {
        int number, count, prev;

        public Node(int number, int count, int prev) {
            this.number = number;
            this.count = count;
            this.prev = prev;
        }
    }

    class Pair {
        int first, second;
        String s;

        public Pair(int first, int second, String s) {
            this.first = first;
            this.second = second;
            this.s = s;
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
        }
    }

    public void solve() throws IOException {
        int n = nextInt();
        a = new Node[n];
        for (int i = 0; i < n; i++) {
            a[i] = new Node(i, 1, i);
        }
        int m = nextInt();
        int k = nextInt();
        for (int i = 0; i < m; i++) {
            n = nextInt();
            n = nextInt();
        }
        ArrayList<Pair> d = new ArrayList<>();
        ArrayList<String> ans = new ArrayList<>();
        for (int i = 0; i < k; i++) {
            String s = nextToken();
            d.add(new Pair(nextInt() - 1, nextInt() - 1, s));
        }
        Collections.reverse(d);
        for (Pair p : d) {
            if (p.s.equals("ask")) {
                if (get(p.first) == get(p.second)) {
                    ans.add("YES");
                } else {
                    ans.add("NO");
                }
            } else {
                union(p.first, p.second);
            }
        }
        Collections.reverse(ans);
        for (String s : ans) {
            out.println(s);
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
        new F().run();
    }

}