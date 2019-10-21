<?php

namespace App\Http\Controllers;

use App\Uav;
use Illuminate\Http\Request;

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
        
        $uav=new Uav;
        $uav->name=request('name');
        $uav->local_ip=request('local_ip');
        $uav->save();

        return redirect('/home');


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
        return view('uavs.edit_uav', compact('uav'));
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
        $uav->delete();
        return redirect('/uavs');
    }
}
