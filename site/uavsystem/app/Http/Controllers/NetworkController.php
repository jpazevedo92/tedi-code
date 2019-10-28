<?php

namespace App\Http\Controllers;

use App\Network;
use Illuminate\Http\Request;

class NetworkController extends Controller
{
    /**
     * Display a listing of the resource.
     *
     * @return \Illuminate\Http\Response
     */
    public function index()
    {
        $networks = Network::all();

        return view("networks.index", compact('networks'));
    }

    /**
     * Show the form for creating a new resource.
     *
     * @return \Illuminate\Http\Response
     */
    public function create()
    {
        return view('networks.insert_network');
    }

    /**
     * Store a newly created resource in storage.
     *
     * @param  \Illuminate\Http\Request  $request
     * @return \Illuminate\Http\Response
     */
    public function store(Request $request)
    {
        $network=new Network;
        $network->if_name=request('if_name');
        $network->tunnel_ip_in=request('tunnel_ip_in');
        $network->tunnel_ip_out=request('tunnel_ip_out');
        $network->network_address=request('network_address');
        $network->mask=request('mask');
        $network->save();

        return redirect('/home');
    }

    /**
     * Display the specified resource.
     *
     * @param  \App\Network  $network
     * @return \Illuminate\Http\Response
     */
    public function show(Network $network)
    {
        //
    }

    /**
     * Show the form for editing the specified resource.
     *
     * @param  \App\Network  $network
     * @return \Illuminate\Http\Response
     */
    public function edit(Network $network)
    {
        return view('networks.edit_network', compact('network'));
    }

    /**
     * Update the specified resource in storage.
     *
     * @param  \Illuminate\Http\Request  $request
     * @param  \App\Network  $network
     * @return \Illuminate\Http\Response
     */
    public function update(Request $request, Network $network)
    {
        $network->if_name=request('if_name');
        $network->tunnel_ip_in=request('tunnel_ip_in');
        $network->tunnel_ip_out=request('tunnel_ip_out');
        $network->network_address=request('network_address');
        $network->mask=request('mask');

        $network->save();
        return redirect('/networks');
    }

    /**
     * Remove the specified resource from storage.
     *
     * @param  \App\Network  $network
     * @return \Illuminate\Http\Response
     */
    public function destroy(Network $network)
    {
        $network->delete();
        return redirect('/networks');
    }
}
