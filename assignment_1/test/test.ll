; ModuleID = 'test.ll'
source_filename = "test.cpp"
target datalayout = "e-m:o-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx15.0.0"

@.str = private unnamed_addr constant [18 x i8] c"Test passo 1: %d\0A\00", align 1
@.str.1 = private unnamed_addr constant [18 x i8] c"Test passo 2: %d\0A\00", align 1
@.str.2 = private unnamed_addr constant [18 x i8] c"Test passo 3: %d\0A\00", align 1
@.str.3 = private unnamed_addr constant [20 x i8] c"Test combinato: %d\0A\00", align 1
@.str.4 = private unnamed_addr constant [20 x i8] c"Test complesso: %d\0A\00", align 1

; Function Attrs: mustprogress noinline nounwind ssp uwtable
define noundef i32 @_Z11test_passo1ii(i32 noundef %0, i32 noundef %1) #0 {
  %3 = add nsw i32 %0, 0
  %4 = add nsw i32 0, %1
  %5 = sub nsw i32 %0, 0
  %6 = mul nsw i32 %0, 1
  %7 = mul nsw i32 1, %1
  %8 = sdiv i32 %0, 1
  %9 = add nsw i32 %3, %4
  %10 = add nsw i32 %9, %5
  %11 = add nsw i32 %10, %6
  %12 = add nsw i32 %11, %7
  %13 = add nsw i32 %12, %8
  ret i32 %13
}

; Function Attrs: mustprogress noinline nounwind ssp uwtable
define noundef i32 @_Z11test_passo2i(i32 noundef %0) #0 {
  %2 = mul nsw i32 %0, 16
  %3 = mul nsw i32 %0, 15
  %4 = mul nsw i32 %0, 17
  %5 = sdiv i32 %0, 8
  %6 = mul nsw i32 %0, -16
  %7 = sdiv i32 %0, -8
  %8 = add nsw i32 %2, %3
  %9 = add nsw i32 %8, %4
  %10 = add nsw i32 %9, %5
  %11 = add nsw i32 %10, %6
  %12 = add nsw i32 %11, %7
  ret i32 %12
}

; Function Attrs: mustprogress noinline nounwind ssp uwtable
define noundef i32 @_Z11test_passo3i(i32 noundef %0) #0 {
  %2 = add nsw i32 %0, 5
  %3 = sub nsw i32 %2, 5
  %4 = sub nsw i32 %0, 7
  %5 = add nsw i32 %4, 7
  %6 = mul nsw i32 %0, 3
  %7 = sdiv i32 %6, 3
  %8 = sdiv i32 %0, 4
  %9 = mul nsw i32 %8, 4
  %10 = sdiv i32 15, 3
  %11 = add nsw i32 %3, %5
  %12 = add nsw i32 %11, %7
  %13 = add nsw i32 %12, %9
  %14 = add nsw i32 %13, %10
  ret i32 %14
}

; Function Attrs: mustprogress noinline nounwind ssp uwtable
define noundef i32 @_Z13test_combinedii(i32 noundef %0, i32 noundef %1) #0 {
  %3 = add nsw i32 %0, 0
  %4 = mul nsw i32 %3, 16
  %5 = mul nsw i32 %0, 8
  %6 = sdiv i32 %5, 8
  %7 = mul nsw i32 %0, 1
  %8 = add nsw i32 %7, 10
  %9 = sub nsw i32 %8, 10
  %10 = mul nsw i32 %0, 16
  %11 = sdiv i32 %10, 2
  %12 = mul nsw i32 %11, 2
  %13 = add nsw i32 %1, 0
  %14 = mul nsw i32 %13, 1
  %15 = mul nsw i32 %14, 4
  %16 = sdiv i32 %15, 4
  %17 = add nsw i32 %4, %6
  %18 = add nsw i32 %17, %9
  %19 = add nsw i32 %18, %12
  %20 = add nsw i32 %19, %16
  ret i32 %20
}

; Function Attrs: mustprogress noinline nounwind ssp uwtable
define noundef i32 @_Z16complex_functioniii(i32 noundef %0, i32 noundef %1, i32 noundef %2) #0 {
  %4 = alloca [50 x i32], align 16
  %5 = add nsw i32 %0, 0
  %6 = getelementptr inbounds [50 x i32], ptr %4, i64 0, i64 0
  store i32 %5, ptr %6, align 16
  %7 = mul nsw i32 %1, 1
  %8 = getelementptr inbounds [50 x i32], ptr %4, i64 0, i64 1
  store i32 %7, ptr %8, align 4
  %9 = sub nsw i32 %2, 0
  %10 = getelementptr inbounds [50 x i32], ptr %4, i64 0, i64 2
  store i32 %9, ptr %10, align 8
  %11 = mul nsw i32 %0, 8
  %12 = getelementptr inbounds [50 x i32], ptr %4, i64 0, i64 3
  store i32 %11, ptr %12, align 4
  %13 = getelementptr inbounds [50 x i32], ptr %4, i64 0, i64 3
  %14 = load i32, ptr %13, align 4
  %15 = sdiv i32 %14, 8
  %16 = getelementptr inbounds [50 x i32], ptr %4, i64 0, i64 4
  store i32 %15, ptr %16, align 16
  %17 = add nsw i32 %1, 5
  %18 = getelementptr inbounds [50 x i32], ptr %4, i64 0, i64 5
  store i32 %17, ptr %18, align 4
  %19 = getelementptr inbounds [50 x i32], ptr %4, i64 0, i64 5
  %20 = load i32, ptr %19, align 4
  %21 = sub nsw i32 %20, 5
  %22 = getelementptr inbounds [50 x i32], ptr %4, i64 0, i64 6
  store i32 %21, ptr %22, align 8
  %23 = mul nsw i32 %2, 16
  %24 = getelementptr inbounds [50 x i32], ptr %4, i64 0, i64 7
  store i32 %23, ptr %24, align 4
  %25 = mul nsw i32 %0, 15
  %26 = getelementptr inbounds [50 x i32], ptr %4, i64 0, i64 8
  store i32 %25, ptr %26, align 16
  %27 = sdiv i32 %1, 4
  %28 = getelementptr inbounds [50 x i32], ptr %4, i64 0, i64 9
  store i32 %27, ptr %28, align 4
  br label %29

29:                                               ; preds = %87, %3
  %.02 = phi i32 [ 10, %3 ], [ %88, %87 ]
  %30 = icmp slt i32 %.02, 50
  br i1 %30, label %31, label %89

31:                                               ; preds = %29
  %32 = srem i32 %.02, 5
  %33 = icmp eq i32 %32, 0
  br i1 %33, label %34, label %42

34:                                               ; preds = %31
  %35 = sub nsw i32 %.02, 10
  %36 = sext i32 %35 to i64
  %37 = getelementptr inbounds [50 x i32], ptr %4, i64 0, i64 %36
  %38 = load i32, ptr %37, align 4
  %39 = add nsw i32 %38, 0
  %40 = sext i32 %.02 to i64
  %41 = getelementptr inbounds [50 x i32], ptr %4, i64 0, i64 %40
  store i32 %39, ptr %41, align 4
  br label %86

42:                                               ; preds = %31
  %43 = srem i32 %.02, 5
  %44 = icmp eq i32 %43, 1
  br i1 %44, label %45, label %53

45:                                               ; preds = %42
  %46 = sub nsw i32 %.02, 5
  %47 = sext i32 %46 to i64
  %48 = getelementptr inbounds [50 x i32], ptr %4, i64 0, i64 %47
  %49 = load i32, ptr %48, align 4
  %50 = mul nsw i32 %49, 1
  %51 = sext i32 %.02 to i64
  %52 = getelementptr inbounds [50 x i32], ptr %4, i64 0, i64 %51
  store i32 %50, ptr %52, align 4
  br label %85

53:                                               ; preds = %42
  %54 = srem i32 %.02, 5
  %55 = icmp eq i32 %54, 2
  br i1 %55, label %56, label %64

56:                                               ; preds = %53
  %57 = sub nsw i32 %.02, 2
  %58 = sext i32 %57 to i64
  %59 = getelementptr inbounds [50 x i32], ptr %4, i64 0, i64 %58
  %60 = load i32, ptr %59, align 4
  %61 = mul nsw i32 %60, 8
  %62 = sext i32 %.02 to i64
  %63 = getelementptr inbounds [50 x i32], ptr %4, i64 0, i64 %62
  store i32 %61, ptr %63, align 4
  br label %84

64:                                               ; preds = %53
  %65 = srem i32 %.02, 5
  %66 = icmp eq i32 %65, 3
  br i1 %66, label %67, label %75

67:                                               ; preds = %64
  %68 = sub nsw i32 %.02, 1
  %69 = sext i32 %68 to i64
  %70 = getelementptr inbounds [50 x i32], ptr %4, i64 0, i64 %69
  %71 = load i32, ptr %70, align 4
  %72 = sdiv i32 %71, 8
  %73 = sext i32 %.02 to i64
  %74 = getelementptr inbounds [50 x i32], ptr %4, i64 0, i64 %73
  store i32 %72, ptr %74, align 4
  br label %83

75:                                               ; preds = %64
  %76 = sub nsw i32 %.02, 4
  %77 = sext i32 %76 to i64
  %78 = getelementptr inbounds [50 x i32], ptr %4, i64 0, i64 %77
  %79 = load i32, ptr %78, align 4
  %80 = sub nsw i32 %79, 0
  %81 = sext i32 %.02 to i64
  %82 = getelementptr inbounds [50 x i32], ptr %4, i64 0, i64 %81
  store i32 %80, ptr %82, align 4
  br label %83

83:                                               ; preds = %75, %67
  br label %84

84:                                               ; preds = %83, %56
  br label %85

85:                                               ; preds = %84, %45
  br label %86

86:                                               ; preds = %85, %34
  br label %87

87:                                               ; preds = %86
  %88 = add nsw i32 %.02, 1
  br label %29, !llvm.loop !6

89:                                               ; preds = %29
  br label %90

90:                                               ; preds = %97, %89
  %.01 = phi i32 [ 0, %89 ], [ %96, %97 ]
  %.0 = phi i32 [ 0, %89 ], [ %98, %97 ]
  %91 = icmp slt i32 %.0, 50
  br i1 %91, label %92, label %99

92:                                               ; preds = %90
  %93 = sext i32 %.0 to i64
  %94 = getelementptr inbounds [50 x i32], ptr %4, i64 0, i64 %93
  %95 = load i32, ptr %94, align 4
  %96 = add nsw i32 %.01, %95
  br label %97

97:                                               ; preds = %92
  %98 = add nsw i32 %.0, 1
  br label %90, !llvm.loop !8

99:                                               ; preds = %90
  ret i32 %.01
}

; Function Attrs: mustprogress noinline norecurse ssp uwtable
define noundef i32 @main() #1 {
  %1 = call noundef i32 @_Z11test_passo1ii(i32 noundef 42, i32 noundef 24)
  %2 = call i32 (ptr, ...) @printf(ptr noundef @.str, i32 noundef %1)
  %3 = call noundef i32 @_Z11test_passo2i(i32 noundef 42)
  %4 = call i32 (ptr, ...) @printf(ptr noundef @.str.1, i32 noundef %3)
  %5 = call noundef i32 @_Z11test_passo3i(i32 noundef 42)
  %6 = call i32 (ptr, ...) @printf(ptr noundef @.str.2, i32 noundef %5)
  %7 = call noundef i32 @_Z13test_combinedii(i32 noundef 42, i32 noundef 24)
  %8 = call i32 (ptr, ...) @printf(ptr noundef @.str.3, i32 noundef %7)
  %9 = call noundef i32 @_Z16complex_functioniii(i32 noundef 42, i32 noundef 24, i32 noundef 10)
  %10 = call i32 (ptr, ...) @printf(ptr noundef @.str.4, i32 noundef %9)
  ret i32 0
}

declare i32 @printf(ptr noundef, ...) #2

attributes #0 = { mustprogress noinline nounwind ssp uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cmov,+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "tune-cpu"="generic" }
attributes #1 = { mustprogress noinline norecurse ssp uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cmov,+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "tune-cpu"="generic" }
attributes #2 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cmov,+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 2, !"SDK Version", [2 x i32] [i32 15, i32 2]}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 8, !"PIC Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{!"Homebrew clang version 19.1.7"}
!6 = distinct !{!6, !7}
!7 = !{!"llvm.loop.mustprogress"}
!8 = distinct !{!8, !7}
