import java.time.LocalTime;

public class InterprocessCommunication 
{
    public static volatile int x = 0;

    public static class Response implements Runnable 
    {
        @Override
        public void run() 
        {
            while (x == 0) 
            {
                Thread.onSpinWait();
                try 
                {
                    Thread.sleep(1000);
                } 
                catch (InterruptedException e) 
                {
                    throw new RuntimeException(e);
                }
            }
            System.out.print("The time is: ");
            System.out.println(LocalTime.now());
        }
    }

    public static class Request implements Runnable 
    {
        @Override
        public void run() 
        {
            System.out.println("What time is it?");
            try 
            {
                Thread.sleep(1000);
            } 
            catch (InterruptedException e) 
            {
                throw new RuntimeException(e);
            }
            x = 1;
        }
    }

    public static void main(String[] args) 
    {
        Request request = new Request();
        Response response = new Response();
        Thread requestThread = new Thread(request);
        Thread responseThread = new Thread(response);
        responseThread.start();
        requestThread.start();
    }
}