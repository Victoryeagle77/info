import java.io.IOException;


public class Incomplet {
	public static void main(String[] args) {
		byte[] txt = {0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x0D, 0x0A};
			try{
		System.out.write(txt);
		}catch(IOException e){}
	}
}
