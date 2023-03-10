using System;
using System.Threading;
using Microsoft.SPOT;
using Microsoft.SPOT.Hardware;
using CTRE.HERO;

namespace Boot_Counter_Example
{
	public class Program
	{
		static OnboardEEPROM e = OnboardEEPROM.Instance;


		public static void Main()
		{

			while(e.CheckHealth() != CTRE.ErrorCode.OK)//don't continue if CheckHealth is not ok
			{
				Debug.Print("CheckHealth() did not return okay");
			}

			// byte arrays for storing data 
			byte[] readData = new byte[256];
			byte[] readData2 = new byte[256];
			byte[] write = new byte[256];
			ulong sec1 = 4096;
			ulong sec2 = 8192;
			e.Read(sec1, readData);//read sector 1 and store the data 
			e.Read(sec2, readData2);//read sector 2 and store the data
			bool chksum = TstChksum(readData);  //test to see if checksum is correct 
			bool chksum2 = TstChksum(readData2);//test to see if checksum is correct 


			if (!chksum&&!chksum2)
				write[0]= 0;	
			else if (!chksum&&chksum2)
				write[0] = readData2[0];
			else if (!chksum2 && chksum)
				write[0] = readData[0];
			else
			{
				if (readData[0] < readData2[0])/// check what sector has newer data 
				{
					write[0] = readData2[0];
				}
				else
				{
					write[0] = readData[0];
				}
			}
			

			System.Threading.Thread.Sleep(100);



			write[0]++;// increment the count 
			CalcandInsert(write);//insert checksum into bytearray
			e.Erase4KB(sec1);//erase the first sector
			e.Write(sec1, write);//write to the first sector


			e.Erase4KB(sec2);//erase the second sector
			e.Write(sec2, write);//write to the second sector

			e.Read(sec1, readData);//read sector 1 
			e.Read(sec2, readData2);//read sector 2 

			/* loop forever */
			while (true)
			{
				CTRE.Native.Watchdog.Feed(120);// feed so green status light will indicate when everything is complete
				if (!chksum && !chksum2)
				{
					Debug.Print("Both checksums from previous data failed count has been reset");
				}
				Debug.Print("boot: " + readData[0]);
				Debug.Print("boot2 " + readData2[0]);



				System.Threading.Thread.Sleep(100);
			}
		}
	static 	bool TstChksum( byte[] test)
		{
			bool retval = false;
			int tot = 0;
			for (int i = 0; i < test.Length; i++)
			{
				if (i < test.Length - 1)
				{
					tot += test[i];

				}
				else
				{
					if ((byte)tot == test[i])
					{
						retval = true;
					}
					else
					{
						retval = false;
					}
				}
			}
			return retval;
		}
		static void CalcandInsert(byte[] test)
		{
			int tot = 0;
			for (int i = 0; i < test.Length; i++)
			{
				if (i < test.Length - 1)
				{
					tot += test[i];

				}
				else
				{
					test[i] = (byte)tot;
				}
			}
		}
	}
}
