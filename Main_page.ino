#include <ESP8266WiFi.h>
void page_Frist(WiFiClient *client)
{
    
    client->flush();
    
    String web = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
    web += "<html>\r\n";
    web += "<head>\r\n";
    web += "<style>\r\n";
    web += ".button-red,.button-blue\r\n"; 
    web += "{color: white;\r\n";
    web += "border-radius: 9px;\r\n";
    web += "font-family:Arial;\r\n";
    web += "font-size:25px;\r\n";
    web += "padding:30px 45px;\r\n";
    web += "}\r\n";
    web += ".button-red:hover:active,.button-blue:hover:active\r\n"; 
    web += "{position:relative;top:3px;color: yellow;}\r\n";
    web += ".button-red {background: rgb(240, 60, 60);}\r\n";
    web += ".button-blue {background: rgb(100,140,255);}\r\n";
    web += "h1{color:black;font-family:Arial;font-size:40px;text-align:center;}\r\n";	      
    web += "</style>\r\n";
    web +="<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/1.12.2/jquery.min.js\"></script>\n";
    web += "<script>\r\n";
    web += "var ajax = null;\r\n";
    web += "if (window.XMLHttpRequest)\r\n";
    web += "{ajax =new XMLHttpRequest();"; 
    web += "}\r\n";
    web += "else\r\n";
    web += "{ajax=new ActiveXObject(\"Microsoft.XMLHTTP\");}\r\n";
    client->print(web);
    ////////////////////////////////////////////
    web = "function ajaxLoad(method ,URL,displayElementId,sendData)\r\n";
    web += "{\r\n";
    web += "if(!ajax){alert(\"not support\");return;}\r\n";
    web += "ajax.open(method,URL,true);\r\n";
    web += "ajax.onreadystatechange = function()\r\n";
    web += "{\r\n";
    web += "if(ajax.readyState == 4 && ajax.status==200)\r\n";
    web += "{\r\n";
    web += "var ajax_result = ajax.responseText;\r\n";
    web += "var el = document.getElementById(displayElementId);\r\n";
    web += "var data_all = ajax.responseText.split(\":\");\n";
    web += "var data_temp = data_all[0];\n";
    web += "var data_Hum  = data_all[1];\n";
    web += "var data_LED_1 = data_all[2];\n";
    web += "var data_LED_2 = data_all[3];\n";
    web += "var Hr         = data_all[4];\n";
    web += "var min        = data_all[5];\n";
    web += "var sec        = data_all[6];\n";
    web += "var day_of_week= data_all[7];\n";
    web += "var day        = data_all[8];\n";
    web += "var mounth      = data_all[9];\n";
    web += "var year       = data_all[10];\n";
//  web +="var canvase_temp_hum = document.getElementById('Temp_Hum');\n";
//  web +="var canvase_temp_hum_context = canvase_temp_hum.getContext('2d');\n";
    web +="draw_Temp_Hum(canvase_temp_hum_context,canvase_temp_hum.width,canvase_temp_hum.height,\"Temp \"+data_temp+ \" C\",\"Hum \"+data_Hum+\" %RH\");\n";
    web +="draw_Date(canvase_date_context,canvase_date.width,canvase_date.height,day_of_week,day,mounth,year);\r\n";
    web +="draw_Time_CLock(canvase_Time_context,canvase_Time.width,canvase_Time.height,Hr,min,sec);\r\n";
//   web +="var canvas = document.getElementById('Led_Canvas');\n";
//   web +="var context = canvas.getContext('2d');\n";
    web +="draw_LAMP(context,centerX/2 ,centerY ,80,data_LED_1);\n";
    web +="draw_LAMP(context,centerX*3/2,centerY,80,data_LED_2);\n";

    web += "}\r\n";
    web += "}\r\n";	
    web += "ajax.send(sendData);\r\n";
    web += "}\r\n";
    client->print(web);
    //////////////////////////////////////////////////////////////////////////////
    web = "function draw_Temp_Hum(ctx,w,h,temp_mass,Hum_mass)\r\n";
    web += "{\r\n";
    web += "ctx.save();\n";   
    web += "ctx.beginPath();\n";
 //   web += "ctx.translate(w, h);\n"; 
    web += "ctx.clearRect(0, 0, w, h);\n";
    web += "ctx.font=\"30px Comic Sans MS\";\n";
    web += "ctx.fillStyle = \"red\";\n";
    web += "ctx.textAlign = \"center\";\n";
    web += "ctx.fillText(temp_mass,w/2,h/4);\n";
    web += "ctx.fillStyle = \"Cyan\";\n";
    web += "ctx.fillText(Hum_mass,w/2,h*3/4);\n";
      web +="ctx.restore();\n";
    web += "}\r\n";
    web += "function update_LED()\r\n";
    web += "{\r\n";
    web += "var URL = \"/LEDSTATUS_.html\";\r\n";
    web += "ajaxLoad(\"GET\",URL,\'led_status\',null);\r\n";
    web += "}\r\n";
    ////////////////////////////////////////////////////////////////////////////////
    client->print(web);
    web = "function draw_Time_CLock(ctx,w,h,Hr,min,sec)\r\n";
    web += "{\r\n";
    web += "ctx.save();\n";   
    web += "ctx.beginPath();\n";
 //   web += "ctx.translate(w, h);\n"; 
    web += "ctx.clearRect(0, 0, w, h);\n";
    web += "ctx.font=\"20px Comic Sans MS\";\n";
    web += "ctx.fillStyle = \"black\";\n";
    web += "ctx.textAlign = \"center\";\n";
    web += "var massage_Time = Hr+\" : \"+min+\" : \"+sec;\n";
    web += "ctx.fillText(massage_Time,w/2,h/2);\n";
    web +="ctx.restore();\n";
    web += "}\r\n";
    ///////////////////////////////////////////////////////////////////////////////
    client->print(web);
    web = "function draw_Date(ctx,w,h,day_of_week,day,mounth,year)\r\n";
    web += "{\r\n";
    web += "ctx.save();\n";   
    web += "ctx.beginPath();\n";
 //   web += "ctx.translate(w, h);\n"; 
    web += "ctx.clearRect(0, 0, w, h);\n";
    web += "ctx.font=\"20px Comic Sans MS\";\n";
    web += "ctx.fillStyle = \"black\";\n";
    web += "ctx.textAlign = \"center\";\n";
    web += "var massage_date = day_of_week+\"  \"+day+\"/\"+mounth+\"/\"+year;\n";
    web += "ctx.fillText(massage_date,w/2,h/2);\n";
    web +="ctx.restore();\n";
    web += "}\r\n";
    ////////////////////////////////////////////////////////////////////////////
    web += "function update_LED_test()\r\n";
    web += "{\r\n";
    web += "var URL_B = \"/LEDS_TEST_.html\";\r\n";
    web += "ajaxLoad(\"GET\",URL_B,\'led_test\',null);\r\n";
    web += "}\r\n";
    ////////////////////////////////////////////////////////////////////////////    
    web += "function update_temp_humi()\r\n"; 
    web += "{\r\n";
    web += "var URL_T = \"/Temp_.html\";\r\n";
    web += "ajaxLoad(\"GET\",URL_T,\'temp_humi\',null);\r\n";
    web += "}\r\n";
    web += "</script>\r\n";
    ////////////////////////////////////////////////////////////////////////////    
    web += "</head>";
    
    web += "<h1 style=\"text-align:Center;\"> Home Automation </h1>\r\n";
    web +="<button type=\"button\" onclick=\"Settime()\">Setting</button>\r\n";
    web += "<h2>\r\n";
    web +="<canvas id=\"Date\" width=\"250\" height=\"50\"></canvas>\r\n";   // << Add canvas date
    web +="<canvas id=\"Time\" width=\"150\" height=\"50\"></canvas>\r\n";   // << Add canvas time
    web +="</h2>\r\n";
    web += "<body>";
    web +="<canvas id=\"Temp_Hum\" width=\"300\" height=\"250\"></canvas><br>\r\n";   // << Add canvas temp
    web +="<canvas id=\"Led_Canvas\" width=\"450\" height=\"250\"></canvas>\r\n";  // << Add canvas LED status


   client->print(web);
    web ="<script>\n";
    web += "function draw_LAMP(ctx,w,h,r,status)\n";
    web += "{\n";
    web += "var radius;\n";
    web += "var grad;\n";
    web += "radius = 100;\n";
    web += "ctx.save();\n";   
    web += "ctx.beginPath();\n";
    web += "ctx.translate(w, h);\n";  
    web += "if(status == 1)\n";
    web += "{\n"; 
    web +="ctx.arc(0, 0, r*0.9 , 0, 2*Math.PI);\n";
    web +="ctx.fillStyle = \"#ffff33\";\n";
    web +="ctx.fill();\n";
    web +="grad = ctx.createRadialGradient(0,0,r*0.85, 0,0,r*0.95);\n";
    web +="grad.addColorStop(0, '#333');\n";
    web +="grad.addColorStop(0.5, 'white');\n";
    web +="grad.addColorStop(1, '#333');\n";
    web +="ctx.strokeStyle = grad;\n";
    web +="ctx.lineWidth = r*0.1;\n";
    web +="ctx.stroke();\n";
    web +="ctx.beginPath();\n";
    web +="ctx.fillStyle = 'black';\n";
    web +="ctx.fill();\n";
    web +="ctx.textBaseline=\"middle\";\n";
    web +="ctx.textAlign=\"center\";\n";
    web +="ctx.font = \"40px Arial\";\n";
    web +="ctx.fillText(\"ON\", 0, 0);\n";
    web +="}\n";
    web +="else if(status == 0)\n";
    web +="{\n";
    web +="ctx.arc(0, 0, r*0.9 , 0, 2*Math.PI);\n";
    web +="ctx.fillStyle = \"#c2c2a3\";\n";
    web +="ctx.fill();\n";
    web +="grad = ctx.createRadialGradient(0,0,r*0.85,0,0,r*0.95);\n";
    web +="grad.addColorStop(0, '#333');\n";
    web +="grad.addColorStop(0.5, 'white');\n";
    web +="grad.addColorStop(1, '#333');\n";
    web +="ctx.strokeStyle = grad;\n";
    web +="ctx.lineWidth = r*0.1;\n";
    web +="ctx.stroke();\n";
    web +="ctx.beginPath();\n";
    web +="ctx.fillStyle = 'black';\n";
    web +="ctx.fill();\n";
    web +="ctx.textBaseline=\"middle\";\n";
    web +="ctx.textAlign=\"center\";\n";
    web +="ctx.font = \"40px Arial\";\n";
    web +="ctx.fillText(\"OFF\", 0, 0);\n";
    web +="}\n";
    web +="ctx.restore();\n";
    web +="}\n";
    web += "</script>\n";
    client->print(web);
    //////////////////////////////////////////////////////////
    web +="<script>\n";
    web +="var canvase_temp_hum = document.getElementById('Temp_Hum');\n";      //Fist  Draw TEMP , HUM
    web +="var canvase_temp_hum_context = canvase_temp_hum.getContext('2d');\n";
    web +="draw_Temp_Hum(canvase_temp_hum_context,canvase_temp_hum.width,canvase_temp_hum.height,\"Temp \"+\"---\"+\" C\",\"Hum \"+\"---\"+\" %RH\");\n";
    
    web +="var canvas = document.getElementById('Led_Canvas');\n";             // Fist Draw LED STATUS
    web +="var context = canvas.getContext('2d');\n";
    web +="var centerX = canvas.width / 2;\n";
    web +="var centerY = canvas.height / 2;\n";
    web +="draw_LAMP(context,centerX/2 ,centerY ,80,0);\n";
    web +="draw_LAMP(context,centerX*3/2,centerY,80,0);\n";
    
    web +="var canvase_date = document.getElementById('Date');\n";      // Draw date
    web +="var canvase_date_context = canvase_date.getContext('2d');\n";
    web +="draw_Date(canvase_date_context,canvase_date.width,canvase_date.height,\"----\",\"-\",\"-\",\"-\");\r\n";
    
    web +="var canvase_Time = document.getElementById('Time');\n";      // Draw Time
    web +="var canvase_Time_context = canvase_Time.getContext('2d');\n";
    web +="draw_Time_CLock(canvase_Time_context,canvase_Time.width,canvase_Time.height,\"-\",\"-\",\"-\");\r\n";
    
    
    web +="</script>\n";
    /////////////////////////////////////////////////////////////////////
    client->print(web);
    web = "</div>\r\n";
    web += "<div><p><input class=\"button-red\" type=\"button\" value=\"Lamp 1 On\" onclick=\"Relay(\'r1on\')\">\r\n";
    web += "<input class=\"button-blue\" type=\"button\" value=\"Lamp 1 Off\" onclick=\"Relay(\'r1off\')\"></P>\r\n";
    web += "<p><input class=\"button-red\" type=\"button\" value=\"Lamp 2 On\" onclick=\"Relay(\'r2on\')\">\r\n";
    web += "<input class=\"button-blue\" type=\"button\" value=\"Lamp 2 Off\" onclick=\"Relay(\'r2off\')\"></P>\r\n";
    web += "</div>\r\n";
    web += "<script>\r\n";
    web += "function Relay(state){ajaxLoad(\"GET\",state+\'.html\',null,null);}\r\n";
    web += "function Settime(){window.location.href='/Settime'}\r\n";	
 
    web += "setInterval(\"update_temp_humi()\",1000);\r\n";
  //  web += "setInterval(\"update_LED()\",3000);\r\n";
  //  web += "setInterval(\"update_LED_test()\",2000);";

      
    web += "</script>";
    web += "</body>";
    web += "</html>";
     client->print(web);
    
}

