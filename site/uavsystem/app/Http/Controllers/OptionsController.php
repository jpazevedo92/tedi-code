<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;

use App\Uav;
use App\Device;
use App\MplsTag;

class OptionsController extends Controller
{
/*  public function open_qgroundcontrol()
    {
        $scripts_folder = "/home/jpazevedo/Repos/tedi-uavcommandforward/1_Code/scripts/general";
        $process=new Process(["python", "init_qgc.py"]);
        $msg=$process->run(function($type, $buffer){
            if (Process::ERR === $type) {
                $msg='ERR > '.$buffer;
            } else {
                $msg='OUT > '.$buffer;
            }
            return $msg;
        });
    
        
        return response()->json(array('msg'=> $msg), 200);
    }

    public function start_vm($id)
    {
        
        $uav=Uav::findOrFail($id);
        $scripts_folder = "/home/jpazevedo/Repos/tedi-uavcommandforward/1_Code/scripts";
        putenv('PATH=/usr/local/bin');
        //dd(is_readable($scripts_folder));
      /*   $process=new Process(["sh", $scripts_folder."/vms/start_vm", $uav->name]);
        $process->run();

        // executes after the command finishes
        if (!$process->isSuccessful()) {
            throw new ProcessFailedException($process);
        }
        $msg = $process->getOutput(); 

        $msg=system("sh ".$scripts_folder."/vms/start_vm ".$uav->name);
        
        return response()->json(array('msg'=> $msg), 200);
    }*/

    public function download_cfg($id){
        $uav = Uav::find($id);
        
        $interfaces_arr = [];

        $routes = $uav->routes;
        $routes_arr = [];
        foreach($routes as $route)
        {
            $in_if = Device::find($route->in_if_id);
            $in_label = MplsTag::find($route->in_tag_id);
            $out_if = Device::find($route->out_if_id);
            $out_label = MplsTag::find($route->out_tag_id);
            array_push($routes_arr, [
                "in_if"         => $in_if->name,
                "in_label"      =>  $in_label->tag,
                "out_if"        => $out_if->name,
                "out_label"     => $out_label->tag
            ]);
        }

        if ($id == 1)
        {
            $myfile = fopen(storage_path('settings/base.json'), "w") or die("Unable to open file!");
            $devices = Device::where("name", "tun1")->orWhere("name", "lo")->get();
        
            foreach($devices as $device)
            {
                array_push($interfaces_arr, [
                    "name" => $device->name,
                    "network" => $device->network->address,
                    "network_mask" => $device->network->mask,
                    "ip" => $device->network->ip_in != NULL ? $device->network->ip_in : $device->network->address,
                ]);
            }            
        }
        else
        {
            $myfile = fopen(storage_path('settings/uav'.$id.'.json'), "w") or die("Unable to open file!");
            $last_id = $id - 1;
            $devices = Device::where("name", "tun".$last_id)->orWhere("name", "tun".$id)->orWhere("name", "lo")->get();
            foreach($devices as $device)
            {
                if($device->name == "tun".$last_id)
                {
                    array_push($interfaces_arr, [
                        "name" => $device->name,
                        "network" => $device->network->address,
                        "network_mask" => $device->network->mask,
                        "ip" => $device->network->ip_out,
                    ]);
                }
                elseif ($device->name == "tun".$id)
                {
                    array_push($interfaces_arr, [
                        "name" => $device->name,
                        "network" => $device->network->address,
                        "network_mask" => $device->network->mask,
                        "ip" => $device->network->ip_in,
                    ]);
                }
                else
                {
                    array_push($interfaces_arr, [
                        "name" => $device->name,
                        "network" => $device->network->address,
                        "network_mask" => $device->network->mask,
                        "ip" => $device->network->ip_in != NULL ? $device->network->ip_in : $device->network->address,
                    ]);
                }
            }

        }
        



        $settings = [
            'name'  => $uav->name,
            'local_ip' => $uav->local_ip,
            'interfaces' => $interfaces_arr,
            'routes'   => $routes_arr,
        ];

        

        
        fwrite($myfile, json_encode($settings, JSON_PRETTY_PRINT | JSON_UNESCAPED_SLASHES | JSON_UNESCAPED_UNICODE));
        fclose($myfile);
        if($id != 1)
            return response()->download(storage_path('settings/uav'.$id.'.json'))->deleteFileAfterSend();
        else
            return response()->download(storage_path('settings/base.json'))->deleteFileAfterSend();
    }

}






