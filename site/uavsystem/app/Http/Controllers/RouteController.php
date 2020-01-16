<?php

namespace App\Http\Controllers;

use App\Route;
use Illuminate\Http\Request;

class RouteController extends Controller
{
    /**
     * Display a listing of the resource.
     *
     * @return \Illuminate\Http\Response
     */
    public function index()
    {
        $routes = Route::all();
        return view("routes.index", compact('routes'));
    }

    /**
     * Show the form for creating a new resource.
     *
     * @return \Illuminate\Http\Response
     */
    public function create()
    {
        return view('routes.insert_route');
    }

    /**
     * Store a newly created resource in storage.
     *
     * @param  \Illuminate\Http\Request  $request
     * @return \Illuminate\Http\Response
     */
    public function store(Request $request)
    {
        ;
        $route=new Route;
        $route->uav_id = request('uav_id');
        $route->in_if_id = request('in_if_id') == 0 ? null : request('in_if_id');
        $route->in_tag_id = request('in_tag_id') == 0 ? null : request('in_tag_id');
        $route->out_if_id = request('out_if_id');
        $route->out_tag_id = request('out_tag_id');
        $route->save();
        return redirect('/routes/create');
    }

    /**
     * Display the specified resource.
     *
     * @param  \App\Route  $route
     * @return \Illuminate\Http\Response
     */
    public function show(Route $route)
    {
        //
    }

    /**
     * Show the form for editing the specified resource.
     *
     * @param  \App\Route  $route
     * @return \Illuminate\Http\Response
     */
    public function edit(Route $route)
    {
        return view('routes.edit_route', compact('route'));
    }

    /**
     * Update the specified resource in storage.
     *
     * @param  \Illuminate\Http\Request  $request
     * @param  \App\Route  $route
     * @return \Illuminate\Http\Response
     */
    public function update(Request $request, Route $route)
    {

        $route->in_if_id = request('in_if_id') == 0 ? null : request('in_if_id');
        $route->in_tag_id = request('in_tag_id') == 0 ? null : request('in_tag_id');
        $route->out_if_id = request('out_if_id');
        $route->out_tag_id = request('out_tag_id');
        $route->save();
        return redirect('/routes');
    }

    /**
     * Remove the specified resource from storage.
     *
     * @param  \App\Route  $route
     * @return \Illuminate\Http\Response
     */
    public function destroy(Route $route)
    {
        $route->delete();
        return redirect('/routes');
    }
}
