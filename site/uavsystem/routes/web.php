<?php

/*
|--------------------------------------------------------------------------
| Web Routes
|--------------------------------------------------------------------------
|
| Here is where you can register web routes for your application. These
| routes are loaded by the RouteServiceProvider within a group which
| contains the "web" middleware group. Now create something great!
|
*/

Route::resource('uavs', "UavController");
Route::resource('devices', "DeviceController");
Route::resource('networks', "NetworkController");
Route::resource('mpls_tags', "MplsTagController");
Route::resource('routes', "RouteController");

Route::delete('/uav_routes/{uav_route}', 'UavController@route_destroy'); 


/* Route::get('/uav/insert', 'UavController@create');
Route::post('/uavs', 'UavController@store');
Route::get('/uavs', 'UavController@index');
Route::get('/uavs/{uav}/edit', 'UavController@edit');
Route::patch('/uavs/{uav}', 'UavController@update');
Route::delete('/uavs/{uav}', 'UavController@destroy'); */
Route::get('/', function () {
    return redirect(route('login'));
});

Route::group(['middleware' => 'auth'], function () {
    //    Route::get('/link1', function ()    {
//        // Uses Auth Middleware
//    });

    //Please do not remove this if you want adminlte:route and adminlte:link commands to works correctly.
    #adminlte_routes
});
