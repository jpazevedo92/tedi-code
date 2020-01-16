@extends('layouts.layout')

@section('htmlheader_title')
	{{ trans('adminlte_lang::message.network') }}
@endsection

@section('box_title')
    {{ trans('adminlte_lang::message.network') }}
@endsection

@section('content')
    @include('networks.networks_table')
@endsection
