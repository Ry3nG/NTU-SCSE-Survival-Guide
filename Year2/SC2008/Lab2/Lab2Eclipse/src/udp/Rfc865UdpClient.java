package udp;

import java.io.UnsupportedEncodingException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;

public class Rfc865UdpClient {
	private static final int QOTD_PORT = 17;
	private static final String SERVER_NAME = "hwlab1.scse.ntu.edu.sg";

	public static void main(String[] args) {
		try (DatagramSocket socket = new DatagramSocket()) {
			InetAddress serverAddress = InetAddress.getByName(SERVER_NAME);
			socket.connect(serverAddress, QOTD_PORT);
			System.out.println("UDP Client connected on port " + QOTD_PORT + " to server: "
					+ serverAddress.getCanonicalHostName());

			String content = "GONG ZERUI, A57, " + InetAddress.getLocalHost().getHostAddress();
			byte[] buf = content.getBytes("UTF-8");
			System.out.println("Content to send: " + content);

			DatagramPacket request = new DatagramPacket(buf, buf.length);
			System.out.println("Sending request...");
			socket.send(request);
			System.out.println("Request sent to server");

			byte[] replyBuf = new byte[512];
			DatagramPacket reply = new DatagramPacket(replyBuf, replyBuf.length);
			System.out.println("Waiting for reply...");
			socket.receive(reply);

			String replyContent = new String(replyBuf, "UTF-8");
			System.out.println("Received reply: " + replyContent);
		} catch (SocketException e) {
			System.err.println("Error creating socket: " + e.getMessage());
		} catch (UnsupportedEncodingException e) {

			System.err.println("Error encoding request content: " + e.getMessage());
		} catch (Exception e) {
			System.err.println("Error communicating with server: " + e.getMessage());
		}
	}
}
