<?php

namespace App\Http\Controllers;

use App\MplsTag;
use Illuminate\Http\Request;

class MplsTagController extends Controller
{
    /**
     * Display a listing of the resource.
     *
     * @return \Illuminate\Http\Response
     */
    public function index()
    {
        $mpls_tags = MplsTag::all();

        return view("mpls_tags.index", compact('mpls_tags'));
    }

    /**
     * Show the form for creating a new resource.
     *
     * @return \Illuminate\Http\Response
     */
    public function create()
    {
        return view('mpls_tags.insert_mpls_tag');
    }

    /**
     * Store a newly created resource in storage.
     *
     * @param  \Illuminate\Http\Request  $request
     * @return \Illuminate\Http\Response
     */
    public function store(Request $request)
    {
        $mpls_tag=new MplsTag;
        $mpls_tag->tag=request('tag');
        $mpls_tag->save();

        return redirect('/mpls_tags/create');
    }

    /**
     * Display the specified resource.
     *
     * @param  \App\MplsTag  $mplsTag
     * @return \Illuminate\Http\Response
     */
    public function show(MplsTag $mplsTag)
    {
        
    }

    /**
     * Show the form for editing the specified resource.
     *
     * @param  \App\MplsTag  $mpls_tag
     * @return \Illuminate\Http\Response
     */
    public function edit(MplsTag $mpls_tag)
    {
        return view('mpls_tags.edit_mpls_tag', compact('mpls_tag'));
    }

    /**
     * Update the specified resource in storage.
     *
     * @param  \Illuminate\Http\Request  $request
     * @param  \App\MplsTag  $mpls_tag
     * @return \Illuminate\Http\Response
     */
    public function update(Request $request, MplsTag $mpls_tag)
    {
        $mpls_tag->tag=request('tag');

        $mpls_tag->save();
        return redirect('/mpls_tags');
    }

    /**
     * Remove the specified resource from storage.
     *
     * @param  \App\MplsTag  $mpls_tag
     * @return \Illuminate\Http\Response
     */
    public function destroy(MplsTag $mpls_tag)
    {
        $mpls_tag->delete();
        return redirect('/mpls_tags');
    }
}
