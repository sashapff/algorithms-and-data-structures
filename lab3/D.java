import java.io.*;
import java.util.*;

public class Parking {
    String fileName = "";

    class Node {
        int i, next;

        public Node(int i, int next) {
            this.i = i;
            this.next = next;
        }
    }

    int n;
    Node[] a;

    int get(int u) {
        if (a[u].next == u) {
            return u;
        }
        int next = get(a[u].next);
        if (u != next && a[u].next != next) {
            a[u].next = next;
        }
        return next;
    }

    void union(int u, int v) {
        u = get(u);
        v = get(v);
        a[u].next = v;
    }

    public void solve() throws IOException {
        n = nextInt();
        a = new Node[n];
        for (int i = 0; i < n; i++) {
            a[i] = new Node(i, i);
        }
        for (int i = 0; i < n; i++) {
            int t = nextInt() - 1;
            int next = get(t);
            out.print((next + 1) + " ");
            union(t, (next + 1) % n);
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
        new Parking().run();
    }

}