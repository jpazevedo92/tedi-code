<?php

namespace App\Http\Controllers;

use App\Uav;
use App\Route;
use Illuminate\Http\Request;
use Illuminate\Support\Facades\DB;

class UavController extends Controller
{
    /**
     * Display a listing of the resource.
     *
     * @return \Illuminate\Http\Response
     */
    public function index()
    {
        $uavs = UAV::all();

        return view("uavs.index", compact('uavs'));
    }

    /**
     * Show the form for creating a new resource.
     *
     * @return \Illuminate\Http\Response
     */
    public function create()
    {
        return view('uavs.insert_uav');
    }

    /**
     * Store a newly created resource in storage.
     *
     * @param  \Illuminate\Http\Request  $request
     * @return \Illuminate\Http\Response
     */
    public function store(Request $request)
    {
        

        //dd($request);
        $uav=new Uav;
        $uav->name=request('name');
        $uav->local_ip=request('local_ip');
        $uav->save();
        $length = count(request('in_if'));
        for ($i = 0; $i < $length; $i++) {
            $route = new Route;
            $route->uav_id=$uav->id;
            $route->in_if_id=request('in_if')[$i] == 0 ? 1 : request('in_if')[$i];
            $route->in_tag_id=request('in_label')[$i] == 0 ? 1 : request('in_label')[$i];
            $route->out_if_id=request('out_if')[$i];
            $route->out_tag_id=request('out_label')[$i];
            $route->save();
        }
        return redirect('/uavs');


    }

    /**
     * Display the specified resource.
     *
     * @param  \App\Uav  $uav
     * @return \Illuminate\Http\Response
     */
    public function show(Uav $uav)
    {
        //
    }

    /**
     * Show the form for editing the specified resource.
     *
     * @param  \App\Uav  $uav
     * @return \Illuminate\Http\Response
     */
    public function edit(Uav $uav)
    {   
        $routes=$uav->routes;
        return view('uavs.edit_uav', compact(['uav', 'routes']));
    }

    /**
     * Update the specified resource in storage.
     *
     * @param  \Illuminate\Http\Request  $request
     * @param  \App\Uav  $uav
     * @return \Illuminate\Http\Response
     */
    public function update(Request $request, Uav $uav)
    {
        $uav->name=request('name');
        $uav->local_ip=request('local_ip');
        $uav->save();

        $routes=$uav->routes;
        
        $length_routes=count($routes);
        $i=0;
        $length = count(request('in_if'));
        if($length > $length_routes){
            
            foreach($routes as $route)
            {
                $route->in_if_id=request('in_if')[$i] == 0 ? 1 : request('in_if')[$i];
                $route->in_tag_id=request('in_label')[$i] == 0 ? 1 : request('in_label')[$i];
                $route->out_if_id=request('out_if')[$i];
                $route->out_tag_id=request('out_label')[$i];
                $route->save();
                $i=$i+1;
            }
            $route = new Route();
            $route->uav_id=$uav->id;
            $route->in_if_id=request('in_if')[$i] == 0 ? 1 : request('in_if')[$i];
            $route->in_tag_id=request('in_label')[$i] == 0 ? 1 : request('in_label')[$i];
            $route->out_if_id=request('out_if')[$i];
            $route->out_tag_id=request('out_label')[$i];
            $route->save();  
        } else {
            foreach($routes as $route)
            {
                $route->in_if_id=request('in_if')[$i] == 0 ? 1 : request('in_if')[$i];
                $route->in_tag_id=request('in_label')[$i] == 0 ? 1 : request('in_label')[$i];
                $route->out_if_id=request('out_if')[$i];
                $route->out_tag_id=request('out_label')[$i];
                $route->save();
                $i += 1;
            } 
        }
     
        return redirect('/uavs');
    }

    /**
     * Remove the specified resource from storage.
     *
     * @param  \App\Uav  $uav
     * @return \Illuminate\Http\Response
     */
    public function destroy(Uav $uav)
    {
        $uav->routes()->delete();
        $uav->delete();
        return redirect('/uavs');
    }

        /**
     * Remove the specified resource from storage.
     *
     * @param  \App\Uav  $uav
     * @return \Illuminate\Http\Response
     */
    public function route_destroy(Uav $uav, $id)
    {
        $route=Route::find($id); 
        $msg = "Successfully deleted";
        $route->delete();    
        return response()->json(array('msg'=> $msg), 200);
    }
}
