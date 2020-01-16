@extends('layouts.layout')

@section('htmlheader_title')
	{{ trans('adminlte_lang::message.uav') }}
@endsection

@section('box_title')
    {{ trans('adminlte_lang::message.uav') }}
@endsection

@section('content')
    @include('uavs.uavs_table')
@endsection

